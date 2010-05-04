/* 
 * File:   goat.c
 * Author: Jason Langenauer
 *
 * Created on 12 November 2009, 6:15 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>
#include <string>

#include "lexer.h"
#include "ast_node.h"
#include "parser.h"
#include "goat.h"
#include "scope.h"

using namespace std;

#ifndef TEST
int main(int argc, char** argv) {
  char prev_cols[100];
  GoatState *G;
    
  G = (GoatState*)malloc( sizeof(GoatState) );
  G->verbose = 0;
  G->sourceFile = NULL;
  
  goatParseArguments( G, argc, argv );

  if (G->sourceFile == NULL) {
    printf("You must supply an input file\n");
    free(G);
    return ( EXIT_FAILURE );
    }
  
  goatLexer( G, G->sourceFile );
  if(G->verbose & VERBOSE_TOKENS) goatPrintTokens( G );

  Parser *parser = new Parser( G->tokens );
  G->astRoot = parser->parse();

  if( G->astRoot == NULL ) return( EXIT_FAILURE );

  if(G->verbose & VERBOSE_AST) {
    memset(prev_cols, 0, 100);
    G->astRoot->print(0, 0, prev_cols );
  }

  Scope *lobby = new Scope( NULL );
  G->astRoot->Analyse( lobby );
  
  delete G->astRoot;
  delete parser;
  free(G);
  return ( EXIT_SUCCESS );
}
#endif

void goatPrintTokens( GoatState *G ) {
    Token *curr = G->tokens;

    if (curr == 0) { printf("No tokens\n"); return; }
    
    printf("Token List\n");

    while(curr != 0) {
        printf("%d ", curr->line_no);
        switch( curr->type ) {
	case Indent:            printf("Indent         ");break;
	case Comment:           printf("Comment        ");break;
	case IndentIncrease:    printf("IndentIncrease ");break;
	case IndentDecrease:    printf("IndentDecrease ");break;
	case Comma:             printf("Comma          ");break;
	case Period:            printf("Period         ");break;
	case Lambda:            printf("Lambda         ");break;
	case Colon:             printf("Colon          ");break;
	case RightParen:        printf("RightParen     ");break;
	case LeftParen:         printf("LeftParen      ");break;
	case Equals:            printf("Equals         ");break;
	case Integer:           printf("Integer        ");break;
	case String:            printf("String         ");break;
	case Identifier:        printf("Identifier     ");break;
	case EndOfFile:         printf("EndOfFile      ");break;
	case Newline:           printf("Newline        ");break;
	case Whitespace:        printf("WhiteSpace     ");break;
	default:                printf("%d            ", curr->type);break;
        }

        switch(curr -> type) {
            case Integer:
            case String:
            case Identifier:
                printf("%s", curr->content);
                break;
	default:
                break;

        }

        printf("\n");
        curr = curr->next;
    }
}

void goatFatalError( const std::string msg ) {
  cout << "FATAL ERROR: %s\n" << msg;
}

#ifndef TEST
// We don't use this during tests so we can replace this function with
// an mocked goatError() to allow us to test that errors are raised. It's
// in test/test_helper.c
void goatError( int lineNo, const std::string fmt, ... ) {
  va_list arg;
  va_start( arg, fmt );
  printf( "\x1b[1;31mError\x1b[0;37;00m[%d]", lineNo );
  vprintf( fmt.c_str(), arg );
  printf("\n");
  va_end(arg);
}
#endif

void goatParseArguments( GoatState *G, int argc, char *argv[]) {
  int i;
  if (argc == 1) {
    printf("Goat - An experimental language\n");
    printf("----------\n");
    printf("Correct usage:\n");
    printf("goat <options> input_file.gt\n");
    printf("options:\n");
    printf("-v              Run in verbose mode.\n");
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
	    G->verbose = G->verbose | VERBOSE_AST;
	    break;
	  // -vLex - print lexical token stream
	  case 'l':
	  case 'L':
	    G->verbose = G->verbose | VERBOSE_TOKENS;
	    break;
	  // -vScope - print scopes
	  case 'S':
	  case 's':
	    G->verbose = G->verbose | VERBOSE_SCOPES;
	    break;
	  }
	break;
      default:
	printf("Invalid option: %s\n", argv[i] );
	exit(0);
      }
    }
    else {
      // Input file
      if(G->sourceFile == NULL) G->sourceFile = argv[i];
    }
  }
}


