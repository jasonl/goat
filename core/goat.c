/* 
 * File:   goat.c
 * Author: Jason Langenauer
 *
 * Created on 12 November 2009, 6:15 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "lexer.h"
#include "goat.h"

#ifndef TEST
int main(int argc, char** argv) {
  GoatState *G;
    
    if (argc < 2) {
        printf("You must supply an input file\n");
        return (EXIT_FAILURE);
    }

    G = (GoatState *)malloc(sizeof(GoatState));

    goatLexer( G, argv[1] );
    goatPrintTokens( G );
    return (EXIT_SUCCESS);
}
#endif

void goatPrintTokens( GoatState *G ) {
    Token *curr = G->tokens;

    if (curr == 0) { printf("No tokens\n"); return; }

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

void goatFatalError( char *msg ) {
    printf("FATAL ERROR: %s\n", msg);
}

