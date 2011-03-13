#include <iostream>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring> // For memset


#include "goat.h"
#include "lexer.h"
#include "assembly_lexer.hpp"

Lexer::Lexer( char* _start, char* _end, SourceFile *_sourceFile ):
  sourceNext(_start), sourceEnd(_end), sourceFile( _sourceFile )
{
  //tokenStream = sourceFile->tokenStream;
  prevIndent = indent = 0;
  currentLine = 1;
  lexerState = Indent;
  thunkStart = thunkEnd = NULL;
}

void Lexer::StartThunk( CodePoint &cp ) {
  thunkStart = sourceCurr;
  thunkEnd = sourceCurr + cp.bytes - 1;
}

void Lexer::StartThunkAtNext( CodePoint &cp ) {
  thunkStart = sourceNext;
  thunkEnd = sourceNext + cp.bytes - 1;
}

void Lexer::PushIndentToken() {
  if( !sourceFile->indentStack.empty() && sourceFile->indentStack.top() != indent ) {
    if( !sourceFile->indentStack.empty() && sourceFile->indentStack.top() < indent) {
      sourceFile->indentStack.push( indent );
      Token newToken( IndentIncrease );
      newToken.SetLineNumber( currentLine );
      sourceFile->tokenStream.push_back( newToken );
    } else {
      Token newToken( IndentDecrease );
      while( !sourceFile->indentStack.empty() && sourceFile->indentStack.top() > indent ) {
	newToken.SetLineNumber( currentLine );
	sourceFile->tokenStream.push_back( newToken );
	sourceFile->indentStack.pop();
      }
    }
  }
}

// Adds a Token to the tokenStream which has content (e.g. Strings etc), pointed to
// by the thunkStart and thunkEnd pointers.
TokenType Lexer::PushToken() {
  size_t thunkLength;
  
  thunkLength = (size_t)(thunkEnd - thunkStart);
  std::string thunk( thunkStart, thunkLength + 1 ); 

  if( thunk == "end" ) return Newline;
  
  Token newToken( lexerState, thunk );
  newToken.SetLineNumber( currentLine );
  TranslateKeywordToken( newToken );
  sourceFile->tokenStream.push_back( newToken );

  if( thunk == "asm" ) {
    AssemblyLexer asmLexer( indent, sourceNext, sourceEnd, sourceFile );
    asmLexer.SetCurrentLine( currentLine );
    asmLexer.Lex();
    sourceNext = asmLexer.GetCurrentPosition();
    currentLine = asmLexer.GetCurrentLine();
    indent = asmLexer.GetIndent();
    return Indent;
  }
  
  return Newline;
}

// Adds a token to the tokenStream which has no content
void Lexer::PushEmptyToken() {
  Token newToken( lexerState );
  newToken.SetLineNumber( currentLine );
  sourceFile->tokenStream.push_back( newToken );
}

// Changes the lexer state according to the next character in the stream
void Lexer::DefaultStateTransitions( CodePoint &cp ) {

  switch( cp.wchar ) 
    {
    case '(': lexerState = LeftParen; break;
    case ')': lexerState = RightParen; break;
    case '"':
      StartThunkAtNext(cp);
      lexerState = String; 
      break;
    case '.': lexerState = Period; break;
    case 0x03bb: lexerState = Lambda; break;
    case ':': lexerState = Colon; break;
    case '=': lexerState = Equals; break;
    case ',': lexerState = Comma; break;
    case ';': lexerState = Comment; break;
    case ' ': lexerState = Whitespace; break;
    case '\n': lexerState = Newline; break;
    default: 
      lexerState = Identifier; 
      StartThunk( cp );
    }
}

// Implements a basic state-machine based tokenizer, which splits the source
// file into a linked list of Tokens. Expects a UTF8-encoded source file, and
// maintains the UTF8 encoding for string literals and identifiers.
void Lexer::Lex() {
  CodePoint cp;
  
  while (sourceNext < sourceEnd) {
    sourceCurr = sourceNext; // Save the address of the current character
    GetNextCodePoint( &cp );

    if ( cp.wchar == '\r') GetNextCodePoint( &cp ); // Ignore '\r' on Windows
    
    switch( lexerState ) 
      {
	
      case Indent: // Indent is just Whitespace before any non-space characters on a line.
	if(cp.wchar == ' ') { indent++; break; }

	if(cp.wchar == '\n') {
	  lexerState = Newline;
	  break;
	}

	PushIndentToken();
	if(cp.wchar >= '0' && cp.wchar <= '9') { 
	  lexerState = Integer; 
	  StartThunk( cp );
	  break;
	}
	DefaultStateTransitions( cp );
	break;

      case Whitespace:
	if(cp.wchar >= 0x30 && cp.wchar <= 0x39) { 
	  lexerState = Integer; 
	  StartThunk( cp );
	  break; 
	}
	DefaultStateTransitions( cp );
	break;

      case RightParen:
      case LeftParen:
      case Colon:
      case Comma:
      case Equals:
      case Period:
      case Lambda:
	PushEmptyToken();
	if(cp.wchar >= 0x30 && cp.wchar <= 0x39) { lexerState = Integer; thunkStart = sourceCurr; thunkEnd = sourceCurr + cp.bytes - 1; break; }
	DefaultStateTransitions( cp );
	break;

      case Comment:
	while(cp.wchar != '\n' && sourceNext < sourceEnd) { 
	  GetNextCodePoint( &cp ); 
	}
	lexerState = Newline;
	break;
	
      case Newline:
	PushEmptyToken();
	indent = 0; currentLine++;
	
	if (cp.wchar == ' ') {
	  indent++;
	  lexerState = Indent;
	  break;
	}

	PushIndentToken();

	switch( cp.wchar ) 
	  {
	  case '(':    lexerState = LeftParen; break;
	  case ')':    lexerState = RightParen; break;		
	  case '"':    lexerState = String; thunkStart=sourceNext; thunkEnd=sourceNext; break;
	  case '.':    lexerState = Period; break;					
	  case 0x03bb: lexerState = Lambda; break;
	  case ':':    lexerState = Colon; break;
	  case '=':    lexerState = Equals; break;		
	  case ',':    lexerState = Comma; break;		
	  case ';':    lexerState = Comment; break;	       
	  case '\n':   lexerState = Newline; break;    
	  default:     lexerState = Identifier; StartThunk( cp );
	  }	
	break;

      case Identifier:
	switch(cp.wchar) 
	  {
	  case '=':    PushToken(); lexerState = Equals; break;
	  case ' ':    PushToken(); lexerState = Whitespace; break;
	  case '\t':   PushToken(); lexerState = Whitespace; break;
	  case '(':    PushToken(); lexerState = LeftParen; break;
	  case 0x03bb: PushToken(); lexerState = Lambda; break;
	  case '.':    PushToken(); lexerState = Period; break;
	  case '"':    PushToken(); lexerState = String; break;
	  case ':':    PushToken(); lexerState = Colon; break;
	  case ',':    PushToken(); lexerState = Comma; break;
	  case ';':    PushToken(); lexerState = Comment; break;	       
	  case ')':    PushToken(); lexerState = RightParen; break;
	  case '\n':   lexerState = PushToken(); break;
	  default:
	    thunkEnd += cp.bytes;
	    break; // If it's not listed above, it's part of the identifier
	  }
	break;
        
      case Integer:
	if( cp.wchar >= '0' && cp.wchar <= '9') { thunkEnd+=cp.bytes; break; }
	PushToken();
	DefaultStateTransitions( cp );
	break;
	
      case String:
	switch( cp.wchar ) 
	  {
	  case '"':
	    thunkEnd--; // Last byte of the previous code point, not the quotation mark
	    PushToken();
	    GetNextCodePoint( &cp ); // Discard the quotation mark
	    DefaultStateTransitions( cp );
	    break;
	  default: thunkEnd += cp.bytes; break;
	  }
	break;
      default:
	break;
      }
  }
  
  // Close out the last token
  switch( lexerState ) 
    {
    case String:
      goatError( currentLine, "Unclosed string found at end of file.");
      break;
    case Integer:
    case Identifier:
      PushToken();
      break;
    default:
      break;
    }

  // Add implied IndentDecrease tokens
  Token newToken( IndentDecrease );
  while( !sourceFile->indentStack.empty() && sourceFile->indentStack.top() > 0 ) {
    newToken.SetLineNumber( currentLine );
    sourceFile->tokenStream.push_back( newToken );
    sourceFile->indentStack.pop();
  }
  
  // Add an End-of-File marker
  lexerState = EndOfFile;
  PushEmptyToken();
}

// Transforms Identifier tokens into keyword tokens.
void Lexer::TranslateKeywordToken( Token &token ) {

  if( token.Type() != Identifier ) return; 

  if( token.Content() == "if" ) {
    token.SetType( If );
    token.ClearContent();
  }

  if( token.Content() == "else" ) {
    token.SetType( Else );
    token.ClearContent();
  }

  if( token.Content() == "class" ) {
    token.SetType( Class );
    token.ClearContent();
  }

  if( token.Content() == "new" ) {
    token.SetType( New );
    token.ClearContent();
  }

  if( token.Content() == "return" ) {
    token.SetType( Return );
    token.ClearContent();
  }

  if( token.Content() == "asm" ) {
    token.SetType( Asm );
    token.ClearContent();
  }
}


// GetNextCodePoint takes a pointer to a CodePoint structure, and then
// copies the next codepoint found in the UTF8 encoded buffer to it. It
// increments the pointer into the buffer automatically.
void Lexer::GetNextCodePoint( CodePoint *cp ) {
  memset(cp, 0, sizeof(CodePoint));

  // Test we don't go beyond the end of the file.
  if (sourceNext > sourceEnd) {
    std::cerr << "Passed end of code block\n";
    return;
  }

  // Convert the character, fill the CodePoint struct and increment
  // the buffer pointers as required
    if ((*sourceNext & 0x80) == 0) {
        // It's a single-byte ASCII charater
        cp->utf8[0] = *sourceNext;
        cp->bytes = 1;
        cp->wchar = (w_char) (cp->utf8[0] & 0x7F);
    } else if ((*sourceNext & 0xE0) == 0xC0) {
        // 2-byte character;
        // TODO: Check that the 2-byte character doesn't take us beyond the
        // end of the buffer.
        cp->utf8[0] = *sourceNext;
        cp->utf8[1] = *(++sourceNext);
        cp->bytes = 2;
        cp->wchar = (((w_char) (cp->utf8[0] & 0x1F)) << 6) |
                    ((w_char) (cp->utf8[1] & 0x3F));
    } else if ((*sourceNext & 0xF0) == 0xE0) {
        // 3-byte character
        cp->utf8[0] = *sourceNext;
        cp->utf8[1] = *(++sourceNext);
        cp->utf8[2] = *(++sourceNext);
        cp->bytes = 3;
        cp->wchar = (((w_char) (cp->utf8[0] & 0x0F)) << 12) |
                    (((w_char) (cp->utf8[1] & 0x3F)) << 6) |
                    ((w_char) (cp->utf8[2] & 0x3F));
    } else if ((*sourceNext & 0xF8) == 0xF0) {
      // 4-byte character
      cp->utf8[0] = *sourceNext;
      cp->utf8[1] = *(++sourceNext);
      cp->utf8[2] = *(++sourceNext);
      cp->utf8[3] = *(++sourceNext);
      cp->bytes = 4;
      cp->wchar = (((w_char) (cp->utf8[0] & 0x07)) << 18) |
	          (((w_char) (cp->utf8[0] & 0x3F)) << 12) |
	          (((w_char) (cp->utf8[1] & 0x3F)) << 6) |
	           ((w_char) (cp->utf8[2] & 0x3F));
    } else {
      std::cerr << "Invalid code point\n";
    }
    ++sourceNext;
}
