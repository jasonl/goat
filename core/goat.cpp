/* 
 * File:   goat.c
 * Author: Jason Langenauer
 *
 * Created on 12 November 2009, 6:15 PM
 */
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <string>

#include "lexer.h"
#include "ast_node.h"
#include "parser.h"
#include "goat.hpp"
#include "scope.h"
#include "source_file.hpp"


#ifndef TEST
int main(int argc, char** argv) {
  int verbose = 0;
  std::string sourceFileName;
  SourceFile *sourceFile = NULL;

  sourceFileName = parseCommandLine( argc, argv, &verbose );

  sourceFile = new SourceFile( sourceFileName );

  sourceFile->Tokenize();
  if( verbose & VERBOSE_TOKENS ) sourceFile->PrintTokens();

  sourceFile->Parse();
  if( verbose & VERBOSE_AST ) sourceFile->PrintAST();

  sourceFile->Analyse();

  delete sourceFile;
  return EXIT_SUCCESS;
}
#endif

void goatFatalError( const std::string msg ) {
  std::cerr << "FATAL ERROR: %s\n" << msg;
}

#ifndef TEST

// We don't use this during tests so we can replace this function with
// an mocked goatError() to allow us to test that errors are raised. It's
// in test/test_helper.c
void goatError( int lineNo, const std::string fmt, ... ) {
  va_list arg;
  va_start( arg, fmt );
  std::cout << "\x1b[1;31mError\x1b[0;37;00m[" << lineNo << "]";
  vfprintf( stdout, fmt.c_str(), arg );
  std::cout << "\n";
  va_end(arg);
}

#endif

std::string parseCommandLine( int argc, char *argv[], int *verbose) {
  int i;
  std::string fileName;

  if (argc == 1) {
    std::cerr << "Goat - An experimental language\n";
    std::cerr << "-------------------------------\n\n";
    std::cerr << "Correct usage:\n";
    std::cerr << "goat <options> input_file.gt\n\n";
    std::cerr << "options:\n";
    std::cerr << "-vlex              Print token stream.\n";
    std::cerr << "-vast              Print AST.\n";
    exit(0);
  }
  
  for ( i=1; i <= (argc - 1); ++i) {

    if(argv[i][0] == '-') {
      // Option switch
      switch( argv[i][1] ){
      case 'V':
      case 'v':
	switch( argv[i][2] ){
	  // -vAST - print the AST
	  case 'a':
	  case 'A':
	    *verbose |= VERBOSE_AST;
	    break;
	  // -vLex - print lexical token stream
	  case 'l':
	  case 'L':
	    *verbose |= VERBOSE_TOKENS;
	    break;
	  // -vScope - print scopes
	  case 'S':
	  case 's':
	    *verbose |= VERBOSE_SCOPES;
	    break;
	  }
	break;
      default:
	std::cerr << "Invalid option: " << argv[i] << "\n";
	exit(0);
      }
    }
    else {
      // Input file
      fileName = argv[i];
    }
  }

  return fileName;
}


