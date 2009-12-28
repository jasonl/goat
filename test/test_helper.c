#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>

#include "lexer.h"
#include "test.h"


int error_count = 0;
int assert_count = 0;
int failure_count = 0;

int main() {
  LexerTest();
  ParserTest();
  printf("%d assertions, %d failures\n", assert_count, failure_count);
  return 0;
}

void assert( int condition, char* message) {
  char failure[] = "\x1b[1;33mTest Failed\x1b[0;37;00m:";
  
  assert_count++;

  if(condition) {
    printf(".");
  } else {
    failure_count++;
    printf("\n%s %s", failure, message);
  }
}

// Creates a dummy token to feed to the parser.
Token *createToken( Token *prev, enum TOKEN_TYPE type, char *content ) {
  Token *newToken = NULL;

  newToken = (Token *)malloc(sizeof(Token));
  memset(newToken, 0, sizeof(Token));
  newToken->type = type;
  newToken->next = NULL;
  newToken->content = content;
  if(prev) prev->next = newToken;
  
  return(newToken);
}

// Mock error function so we can test for errors;
void goatError( int line_no, char *fmt, ... ) {
  va_list arg;
  va_start( arg, fmt );
  error_count++;
  va_end( arg );
}
