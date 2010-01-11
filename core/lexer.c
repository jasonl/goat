#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include "goat.h"
#include "lexer.h"

#define DEFAULT_LEXER_STATE_TRANSITIONS( next_char ) \
  switch( next_char ) {							\
 case '(': lexer_state = LeftParen; break;				\
 case ')': lexer_state = RightParen; break;				\
 case '"': lexer_state = String; thunk_start=next; thunk_end=next; break; \
 case '.': lexer_state = Period; break;					\
 case 0x03bb: lexer_state = Lambda; break;     \
 case ':': lexer_state = Colon; break;	       \
 case '=': lexer_state = Equals; break;	       \
 case ',': lexer_state = Comma; break;	       \
 case ';': lexer_state = Comment; break;       \
 case ' ': lexer_state = Whitespace; break;    \
 case '\n': lexer_state = Newline; break;      \
 case '\r': lexer_state = Newline; break;      \
 default: lexer_state = Identifier; thunk_start = curr; thunk_end=curr+cp.bytes-1; \
}

// Implements a basic state-machine based tokenizer, which splits the source
// file into a linked list of Tokens. Expects a UTF8-encoded source file, and
// maintains the UTF8 encoding for string literals and identifiers.
int goatLexer( GoatState *G, char* sourceFileName ) {
    int indent=0, prev_indent=0, line_no = 1; // Number of indent spaces on the current and previous lines
    char *curr, *next, *end; // Position pointers into the source code
    char *thunk_start = 0, *thunk_end = 0;  // Thunk pointers for the current token
    CodePoint cp;
    enum TOKEN_TYPE lexer_state = Indent;
    Token *t, *last_token; //

    // Load the file into memory, and set the pointers to it
    goatMapFileToMemory( sourceFileName, &next, &end );

    // Generate an empty first token
    t = (Token *)malloc(sizeof(Token));

    if(next == MAP_FAILED) {
        return 0;
    }

    while (next < end) {
        curr = next; // Save the address of the current character
        goatGetNextCodePoint( &cp, &next, &end);

	// Ignore \r
	if ( cp.wchar == '\r') goatGetNextCodePoint( &cp, &next, &end );
	
	// Print the character in verbose mode
        if (G->verbose) printf("%s", cp.utf8);

        switch( lexer_state ) {

            case Indent: // Indent is just Whitespace before any non-space characters on a line.
                if(cp.wchar == ' ') { indent++; break; }
                PUSH_INDENT_TOKEN;
                if(cp.wchar >= 0x30 && cp.wchar <= 0x39) { lexer_state = Integer; thunk_start = curr; thunk_end = curr+cp.bytes-1; break; }
                DEFAULT_LEXER_STATE_TRANSITIONS(cp.wchar);
                break;

            case Whitespace:
                if(cp.wchar >= 0x30 && cp.wchar <= 0x39) { lexer_state = Integer; thunk_start = curr; thunk_end = curr+cp.bytes-1; break; }
                DEFAULT_LEXER_STATE_TRANSITIONS(cp.wchar);
                break;

            case RightParen:
            case LeftParen:
            case Colon:
            case Comma:
            case Equals:
            case Period:
            case Lambda:
                PUSH_EMPTY_TOKEN;
                if(cp.wchar >= 0x30 && cp.wchar <= 0x39) { lexer_state = Integer; thunk_start = curr; thunk_end = curr+cp.bytes-1; break; }
                DEFAULT_LEXER_STATE_TRANSITIONS(cp.wchar);
                break;

            case Comment:
                while(cp.wchar != '\n' && next < end) { 
		  goatGetNextCodePoint( &cp, &next, &end); 
		  if(G->verbose) printf("%s", cp.utf8); 
		}
		lexer_state = Newline;
		break;

	    case Newline:
	        PUSH_EMPTY_TOKEN;
                prev_indent = indent; indent = 0; line_no++;

		if (cp.wchar == ' ' || cp.wchar == '\t') {
		  lexer_state = Indent;
		  break;
		}

		PUSH_INDENT_TOKEN;

		switch( cp.wchar ) {
		case '(': lexer_state = LeftParen; PUSH_EMPTY_TOKEN; break;
		case ')': lexer_state = RightParen; PUSH_EMPTY_TOKEN; break;		
		case '"': lexer_state = String; thunk_start=next; thunk_end=next; break;
		case '.': lexer_state = Period; PUSH_EMPTY_TOKEN;  break;					
		case 0x03bb: lexer_state = Lambda; PUSH_EMPTY_TOKEN; break;
		case ':': lexer_state = Colon; PUSH_EMPTY_TOKEN; break;
		case '=': lexer_state = Equals; PUSH_EMPTY_TOKEN; break;		
		case ',': lexer_state = Comma; PUSH_EMPTY_TOKEN; break;		
		case ';': lexer_state = Comment; break;	       
		case '\n': lexer_state = Newline; break;    
		default: lexer_state = Identifier; thunk_start = curr; thunk_end=curr+cp.bytes-1; \
		}	
		break;

            case Identifier:
	      switch(cp.wchar) {
	      case '=': PUSH_TOKEN; lexer_state = Equals; break;
	      case ' ': PUSH_TOKEN; lexer_state = Whitespace; break;
	      case '\t': PUSH_TOKEN; lexer_state = Whitespace; break;
	      case '(': PUSH_TOKEN; lexer_state = LeftParen; break;
	      case 0x03bb: PUSH_TOKEN; lexer_state = Lambda; break;
	      case '.': PUSH_TOKEN; lexer_state = Period; break;
	      case '"': PUSH_TOKEN; lexer_state = String; break;
	      case ':': PUSH_TOKEN; lexer_state = Colon; break;
	      case ',': PUSH_TOKEN; lexer_state = Comma; break;
	      case ')': PUSH_TOKEN; lexer_state = RightParen; break;
	      case '\n': PUSH_TOKEN; lexer_state = Newline; break;
	      default:
		thunk_end+=cp.bytes;
		break; // If it's not listed above, it's part of the identifier
	      }
	      break;
                
            case Integer:
                if( cp.wchar >= '0' && cp.wchar <= '9') { thunk_end+=cp.bytes; break; }
                PUSH_TOKEN;
                DEFAULT_LEXER_STATE_TRANSITIONS(cp.wchar);
                break;

            case String:
                switch(cp.wchar) {
                    case '"':
                       thunk_end--; // Last byte of the previous code point, not the quotation mark
                       PUSH_TOKEN;
                       goatGetNextCodePoint( &cp, &next, &end); // Discard the quotation mark
                       DEFAULT_LEXER_STATE_TRANSITIONS(cp.wchar);
                       break;
                    default: thunk_end+=cp.bytes; break;
                }
                break;
            default:
                break;
        }
    }
    
    // Close out the last token
    switch( lexer_state ) {
    case String:
      goatError( line_no, "Unclosed string found at end of file.");
      break;
    case Integer:
    case Identifier:
      PUSH_TOKEN;
      break;
    default:
      break;
    }

    goatTranslateKeywordTokens( G );
    
    // Add an End-of-File marker
    lexer_state = EndOfFile;
    PUSH_EMPTY_TOKEN;

    return 1;
}

// After the first tokenizing pass, the lexer will have created Identifier
// tokens for all non-quoted strings of characters, including keywords such
// as "if", "end", "else" etc. This function iterates over the token stream,
// and changes those tokens.
void goatTranslateKeywordTokens( GoatState *G ) {
  Token *curr_token, *next_token, *prev_token;

  next_token = curr_token = G->tokens;

  while( next_token ) {
    prev_token = curr_token;
    curr_token = next_token;

    if(curr_token->type != Identifier || curr_token->content == NULL) {
      next_token = curr_token->next;
      continue;
    }
    
    next_token = curr_token->next;

    if( strcmp("end", curr_token->content) == 0 ) {
      prev_token->next = next_token;
      free(curr_token->content);
      free(curr_token);
      continue;
    }

    if( strcmp("if", curr_token->content) == 0 ) {
      curr_token->type = If;
      free(curr_token->content);
      curr_token->content = NULL;
      continue;
    }

    if( strcmp("else", curr_token->content) == 0 ) {
      curr_token->type = Else;
      free(curr_token->content);
      curr_token->content = NULL;
      continue;
    }

    if( strcmp("class", curr_token->content) == 0 ) {
      curr_token->type = Class;
      free(curr_token->content);
      curr_token->content = NULL;
      continue;
    }
    
    /*    if( strcmp("return", curr_token->content) == 0 ) {
      curr_token->type = Return;
      free(curr_token->content);
      curr_token->content = NULL;
      continue;
      }*/
  }
}


// Creates a mapping between the source file on disk and the buffer in memory.
void goatMapFileToMemory( char * sourceFileName, char **next, char **end) {
    int fp;
    size_t size;
    struct stat sb;

    fp = open(sourceFileName, O_RDONLY);

    // Get the file size
    if(fstat(fp, &sb) == -1) {
        printf("Error getting file stat");
        return;
    }
    size = sb.st_size;

    (*next) = (char *) mmap( NULL, size, PROT_READ, MAP_SHARED, fp, 0);
    (*end) = (*next) + size;

    if ((*next) == MAP_FAILED) {
        printf("Map failed\n");
    }
}


// goatGetNextCodePoint takes a pointer to a CodePoint structure, and then
// copies the next codepoint found in the UTF8 encoded buffer to it. It
// increments the pointer into the buffer automatically.
void goatGetNextCodePoint(CodePoint *cp, char **curr, char **end) {
    memset(cp, 0, sizeof(CodePoint));

    // Test we don't go beyond the end of the file.
    if (*curr > *end) {
        printf("Passed end of code block\n");
        return;
    }

    // Convert the character, fill the CodePoint struct and increment
    // the buffer pointers as required
    if ((**curr & 0x80) == 0) {
        // It's a single-byte ASCII charater
        cp->utf8[0] = **curr;
        cp->bytes = 1;
        cp->wchar = (w_char) (cp->utf8[0] & 0x7F);
    } else if ((**curr & 0xE0) == 0xC0) {
        // 2-byte character;
        // TODO: Check that the 2-byte character doesn't take us beyond the
        // end of the buffer.
        cp->utf8[0] = **curr;
        cp->utf8[1] = *(++(*curr));
        cp->bytes = 2;
        cp->wchar = (((w_char) (cp->utf8[0] & 0x1F)) << 6) |
                    ((w_char) (cp->utf8[1] & 0x3F));
    } else if ((**curr & 0xF0) == 0xE0) {
        // 3-byte character
        cp->utf8[0] = **curr;
        cp->utf8[1] = *(++(*curr));
        cp->utf8[2] = *(++(*curr));
        cp->bytes = 3;
        cp->wchar = (((w_char) (cp->utf8[0] & 0x0F)) << 12) |
                    (((w_char) (cp->utf8[1] & 0x3F)) << 6) |
                    ((w_char) (cp->utf8[2] & 0x3F));
    } else if ((**curr & 0xF8) == 0xF0) {
        // 4-byte character
        cp->utf8[0] = **curr;
        cp->utf8[1] = *(++(*curr));
        cp->utf8[2] = *(++(*curr));
        cp->utf8[3] = *(++(*curr));
        cp->bytes = 4;
        cp->wchar = (((w_char) (cp->utf8[0] & 0x07)) << 18) |
                    (((w_char) (cp->utf8[0] & 0x3F)) << 12) |
                    (((w_char) (cp->utf8[1] & 0x3F)) << 6) |
                    ((w_char) (cp->utf8[2] & 0x3F));
    } else {
        printf("Invalid code point\n");
    }
    ++(*curr);
}
