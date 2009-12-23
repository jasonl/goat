#include <stdio.h>
#include <malloc.h>

#include "lexer.h"
#include "test.h"

int error_count = 0;

void assert( int condition, char* message) {
  char failure[] = "\x1b[1;33mTest Failed\x1b[0;37;00m:";

  if(condition) {
    printf(".");
  } else {
    printf("\n%s %s", failure, message);
  }
}

// Creates a dummy token to feed to the parser.
Token *createToken( Token *prev, enum TOKEN_TYPE type, char *content ) {
  Token *newToken = NULL;

  newToken = (Token *)malloc(sizeof(Token));
  newToken->type = type;
  newToken->next = NULL;
  newToken->content = content;
  if(prev) prev->next = newToken;
  
  return(newToken);
}

// Mock error function so we can test for errors;
void goatError( int line_no, char *fmt, ... ) {
  error_count++;
}
