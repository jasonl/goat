#include <iostream>

#include "lexer.h"
#include "assembly_lexer.hpp"

void AssemblyLexer::AssemblyStateTransitions( CodePoint &cp ) {
  switch( cp.wchar ) {
  case ' ':  lexerState = Whitespace; break;
  case '[':  lexerState = LeftSquare; break;
  case ']':  lexerState = RightSquare; break;
  case ';':  lexerState = Comment; break;
  case ',':  lexerState = Comma; break;
  case '+':  StartThunk( cp ); lexerState = Plus; break;
  case '-':  StartThunk( cp ); lexerState = Minus; break;
  case '*':  StartThunk( cp ); lexerState = Multiply; break;
  case '\n': lexerState = Newline; break;
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
    lexerState = Integer;
    StartThunk( cp );
    break;
  default:
    lexerState = Identifier;
    StartThunk( cp );
  }
}

// AssemblyLexer::Lex()
// 
// The assembly lexer is instantiated, and begins scanning the input from the 
// character immediately after the "asm" keyword, and continues scanning
// until the identing of the line is less than or equal to the base indent of 
// the asm token.
//
//     asm
//        ^ AssemblyLexer commences here, before the Newline token
//       mov eax, 3
//       ...
//       int 32
//
//     if( something )
//    ^ AssemblyLexer finishes here, after pushing the IndentDecrease token
//
void AssemblyLexer::Lex() {
  CodePoint cp;
  bool firstLine = true;

  GetNextCodePoint( &cp );

  // TODO: suck up whitespace after the asm token

  if( cp.wchar != '\n' ) {
    lexerState = Newline;
    PushEmptyToken();
  } else {
    // Raise an error
    return;
  }

  lexerState = Indent;
  
  while( sourceNext <= sourceEnd ){
    sourceCurr = sourceNext;
    GetNextCodePoint( &cp );
    
    switch( lexerState ) {
    case Indent:
      if(cp.wchar == ' ') { indent++; break; }

      if( firstLine ) {
	PushIndentToken();
	firstLine = false;
      }

      if( indent < baseIndent ) {
	PushIndentToken();
	return;
      }
      
      AssemblyStateTransitions( cp );
      break;

    case Newline:
      PushEmptyToken();
      prevIndent = indent; indent = 0; currentLine++;
      if (cp.wchar == ' ' || cp.wchar == '\t') {
	lexerState = Indent;
	break;
      }

      PushIndentToken();
      break;
      
    case Whitespace:
      AssemblyStateTransitions( cp );
      break;

    case Comment:
      while(cp.wchar != '\n' && sourceNext < sourceEnd) { 
	GetNextCodePoint( &cp ); 
      }
      GetNextCodePoint( &cp );
      prevIndent = indent; indent = 0; currentLine++;
      lexerState = Indent;
      break;
      
    case Plus:
    case Minus:
    case Multiply:
    case Label:
      PushToken(); // We want to keep the operator in the Token
      AssemblyStateTransitions( cp );
      break;

    case Comma:
    case LeftSquare:
    case RightSquare:
      PushEmptyToken();
      AssemblyStateTransitions( cp );
      break;

    case Integer:
      if( cp.wchar >= '0' && cp.wchar <= '9') { thunkEnd+=cp.bytes; break; }
      PushToken();
      AssemblyStateTransitions( cp );
      break;

    case Identifier:
      switch(cp.wchar) {
      case ' ':  PushToken(); lexerState = Whitespace; break;
      case '[':  PushToken(); lexerState = LeftSquare; break;
      case ']':  PushToken(); lexerState = RightSquare; break;
      case ',':  PushToken(); lexerState = Comma; break;
      case '+':  PushToken(); StartThunk( cp ); lexerState = Plus; break;
      case '-':  PushToken(); StartThunk( cp ); lexerState = Minus; break;
      case '*':  PushToken(); StartThunk( cp ); lexerState = Multiply; break;
      case '\n': PushToken(); lexerState = Newline; break;
      case ':':  lexerState = Label; thunkEnd += cp.bytes; break;
      default:
	thunkEnd += cp.bytes;
	break;
      }
      
      break;
    default:
      std::cout << "Invalid lexer state identified in AssemblyLexer";
    }    
  }

  // Handle the end of file if we encounter it
  switch( lexerState ) {
  case Identifier:
  case Label:
  case Integer:
    PushToken();
  default:
    break;
  }
    
}
