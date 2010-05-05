#include <string>
#include <iostream>
#include "malloc.h" // For free -- TO BE REMOVED
#include <cstring> // For memset

#include "ast_node.h"
#include "lexer.h"
#include "scope.h"
#include "parser.h"
#include "source_file.hpp"

SourceFile::SourceFile( std::string _fileName ) {
  fileName = _fileName;
  tokenStream = NULL;
  astRoot = NULL;
  lobby = NULL;
}

SourceFile::~SourceFile() {
  Token *lastToken;

  // Free the memory allocated for the tokens
  //while( tokenStream ) {
  //  lastToken = tokenStream;
  //  tokenStream = lastToken->next;
  //  free(lastToken);
  // }

  // Free the AST
  if( astRoot ) delete astRoot;

  // Free the Scope tree
  // TODO - We need to iterate over all scopes somehow
  if( lobby ) delete lobby;
}

void SourceFile::Tokenize() {
  tokenStream = goatLexer( fileName );
}

// Parse()
// Transforms the stream of tokens into an Abstract Syntax Tree
void SourceFile::Parse() {
  if( tokenStream) {
    Parser *parser = new Parser( tokenStream );
    astRoot = parser->Parse();
  } else {
    std::cerr << "Unable to parse source file. No tokens found";
  }
}

void SourceFile::Analyse() {
  lobby = new Scope( NULL );

  if( astRoot ) {
    astRoot->Analyse( lobby );
  } else {
    std::cerr << "No Abstract Syntax Tree was built from this source file";
  }
}

void SourceFile::PrintTokens() {
  Token *curr = tokenStream;

  if (curr == 0) { 
    std::cout << "No tokens\n"; 
    return; 
  }
    
  std::cout << "Token List\n";

  while( curr ) {
    std::cout << curr->line_no;
    switch( curr->type ) 
      {
      case Indent:            std::cout << "Indent         "; break;
      case Comment:           std::cout << "Comment        "; break;
      case IndentIncrease:    std::cout << "IndentIncrease "; break;
      case IndentDecrease:    std::cout << "IndentDecrease "; break;
      case Comma:             std::cout << "Comma          "; break;
      case Period:            std::cout << "Period         "; break;
      case Lambda:            std::cout << "Lambda         "; break;
      case Colon:             std::cout << "Colon          "; break;
      case RightParen:        std::cout << "RightParen     "; break;
      case LeftParen:         std::cout << "LeftParen      "; break;
      case Equals:            std::cout << "Equals         "; break;
      case Integer:           std::cout << "Integer        "; break;
      case String:            std::cout << "String         "; break;
      case Identifier:        std::cout << "Identifier     "; break;
      case EndOfFile:         std::cout << "EndOfFile      "; break;
      case Newline:           std::cout << "Newline        "; break;
      case Whitespace:        std::cout << "WhiteSpace     "; break;
      default:                std::cout << curr->type;        break;
      }
      
    switch(curr -> type) 
      {
      case Integer:
      case String:
      case Identifier:
	std::cout << curr->content;
	break;
      default:
	break;
      }
	
    std::cout << "\n";
    curr = curr->next;
    }
}

void SourceFile::PrintAST() {
  char prev_cols[100];
  
  if( astRoot ) {
    memset( prev_cols, 0, 100 );
    astRoot->print( 0, 0, prev_cols );
  } else {
    std::cout << "No AST Nodes found.\n";
  }
}
