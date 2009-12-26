/* 
 * File:   lexer.h
 * Author: jason
 *
 * Created on 12 November 2009, 6:18 PM
 */

#ifndef _LEXER_H
#define	_LEXER_H

// 32-bit wide integer to hold the code-point value
typedef unsigned long w_char;

// Token types
enum TOKEN_TYPE { Whitespace,
                  Indent,
                  Comment,
                  Newline,
                  Identifier,
                  RightParen,
                  LeftParen,
                  Lambda,
                  Colon,
                  Period,
                  Comma,
                  Equals,
                  End,
                  Integer,
                  String,
                  If,
                  Else,
		  Return,
		  Class,
                  HashRocket,
                  IndentIncrease,
                  IndentDecrease
                  };

// holds a lexical token
typedef struct _Token {
    enum TOKEN_TYPE type;
    int line_no;
    char *content;
    struct _Token *next;
} Token;

// This struct holds the UTF-8 and Unicode representation
typedef struct {
    w_char wchar;            // The unencoded value
    int bytes;               // Number of bytes in the code point.
    char utf8[4];            // UTF-8 encoded value
} CodePoint;

// Inline macros to push tokens onto the linked list of tokens.
#define PUSH_INDENT_TOKEN \
  if(prev_indent != indent ) { \
    if(prev_indent < indent) { \
      t->type = IndentIncrease; t->content = 0; t->line_no = line_no; \
      if(G->tokens == 0) { G->tokens = t; } else { last_token->next = t; } \
      last_token = t; t = (Token *)malloc(sizeof(Token)); \
    } else { \
      t->type = IndentDecrease; t->content = 0; t->line_no = line_no; \
      if(G->tokens == 0) { G->tokens = t; } else { last_token->next = t; } \
      last_token = t; t = (Token *)malloc(sizeof(Token)); \
    } \
  }

// Pushes a token onto the end of the token list, and stores the current thunk
// in that token, as we want to use it later (e.g. string literals, indentifiers etc)
#define PUSH_TOKEN \
  t->type = lexer_state; t->line_no = line_no;\
  t->content = (char *) malloc( (thunk_end - thunk_start) + 3 ); \
  strncpy(t->content, thunk_start, (thunk_end - thunk_start) + 1); \
  if(G->tokens == 0) { G->tokens = t; } else { last_token->next = t; } \
  last_token = t; t = (Token *)malloc(sizeof(Token));

// Pushes a token onto the end of the token list, but ignores the current thunk
#define PUSH_EMPTY_TOKEN \
  t->type = lexer_state; t->line_no = line_no;\
  if(G->tokens == 0) { G->tokens = t; } else { last_token->next = t; } \
  last_token = t; t = (Token *)malloc(sizeof(Token)); \

// Function prototypes
struct _GoatState; // declared in goat.h

int goatLexer( struct _GoatState*, char* );
void goatMapFileToMemory( char*, char**, char** );
void goatGetNextCodePoint( CodePoint*, char**, char**);
void goatTranslateKeywordTokens( struct _GoatState* );
#endif	/* _LEXER_H */

