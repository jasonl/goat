/* 
 * File:   goat.c
 * Author: Jason Langenauer
 *
 * Created on 12 November 2009, 6:15 PM
 */
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("You must supply an input file\n");
        return (EXIT_FAILURE);
    }
    goatLexer( argv[1] );
    return (EXIT_SUCCESS);
}

