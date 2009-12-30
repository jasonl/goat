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

#include "lexer.h"
#include "ast.h"
#include "goat.h"

#ifndef TEST
int main(int argc, char** argv) {
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
  if(G->verbose) goatPrintTokens( G );

  goatBuildAST( G );
  if( G->astRoot == NULL ) return( EXIT_FAILURE );

  if(G->verbose) goatPrintASTNode( G->astRoot, 0 );

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
	default:                printf("???            ");break;
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

void goatPrintASTNode( Node *node, int depth ) {
  Node *lastChild;
  int i;
  
  printf("%s\n", NODE_TYPES[node->type]);
  
  if( node->firstChild == NULL ) {
    return;
  }
  
  lastChild = node->firstChild;
  while( (int)lastChild ) {
    i = 0;
    while(i < depth) {
      printf("\u2502");
      i++;
    }

    if (lastChild->nextSibling == NULL) {
      printf("\u2514");
    } else {
      printf("\u251c");
    }
    
    goatPrintASTNode(lastChild, depth+1);
    lastChild = lastChild->nextSibling;
  }
}

void goatFatalError( char *msg ) {
    printf("FATAL ERROR: %s\n", msg);
}

#ifndef TEST
// We don't use this during tests so we can replace this function with
// an mocked goatError() to allow us to test that errors are raised. It's
// in test/test_helper.c
void goatError( int lineNo, char *fmt, ... ) {
  va_list arg;
  va_start( arg, fmt );
  printf( "\x1b[1;31mError\x1b[0;37;00m[%d]", lineNo );
  vprintf( fmt, arg );
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
      case 'v':
	G->verbose = 1;
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


