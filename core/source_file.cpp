#include <string>
#include <iostream>
#include <cstdio>
#include <fcntl.h>
#include "malloc.h" // For free -- TO BE REMOVED
#include <cstring> // For memset
#include <sys/mman.h> // For mmap
#include <sys/stat.h>

#include "ast_node.h"
#include "lexer.h"
#include "scope.h"
#include "parser.h"
#include "source_file.hpp"

SourceFile::SourceFile( std::string _fileName ) {
  fileName = _fileName;
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
  int fp;
  size_t size;
  struct stat sb;
  char *start, *end;

  fp = open(fileName.c_str(), O_RDONLY);
  
  // Get the file size
  if(fstat(fp, &sb) == -1) {
    printf("Error getting file stat");
    return;
  }
  size = sb.st_size;

  start = (char *) mmap( NULL, size, PROT_READ, MAP_SHARED, fp, 0);
  end = start + size;
  
  if( start == MAP_FAILED ) {
    printf("Map failed\n");
  }
  
  Lexer *lexer = new Lexer( start, end, this );
  lexer->Lex();
}

// Parse()
// Transforms the stream of tokens into an Abstract Syntax Tree
void SourceFile::Parse() {
  if( ! tokenStream.empty() ) {
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
  std::list<Token>::iterator curr = tokenStream.begin();

  std::cout << "Token List\n";

  for( std::list<Token>::iterator curr = tokenStream.begin(); curr != tokenStream.end(); curr++) {
    std::cout << curr->LineNumber() << " ";
    switch( curr->Type() ) 
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
      default:                std::cout << curr->Type();        break;
      }
      
    switch( curr->Type() ) 
      {
      case Integer:
      case String:
      case Identifier:
	std::cout << curr->Content();
	break;
      default:
	break;
      }
	
    std::cout << "\n";
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