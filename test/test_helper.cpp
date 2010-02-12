#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <iostream>

#include "lexer.h"
#include "test.h"

using namespace std;

int ParserTest::error_count = 0;
int assert_count = 0;
int failure_count = 0;

int main() {
  LexerTest();
  ParserTest p = ParserTest();
  printf("%d assertions, %d failures\n", assert_count, failure_count);
  return 0;
}

void assert( int condition, std::string message) {
  string failure = "\x1b[1;33mTest Failed\x1b[0;37;00m:";
  
  assert_count++;

  if(condition) {
    printf(".");
  } else {
    failure_count++;
    cout << endl << failure << message;
  }
}

// Creates a dummy token to feed to the parser.
Token *ParserTest::createToken( Token *prev, enum TOKEN_TYPE type, const string content ) {
  Token *newToken = NULL;

  newToken = (Token *)malloc(sizeof(Token));
  memset(newToken, 0, sizeof(Token));
  newToken->type = type;
  newToken->next = NULL;
  newToken->content = (char *)content.c_str();
  if(prev) prev->next = newToken;
  
  return(newToken);
}

// Mock error function so we can test for errors;
void goatError( int line_no, string fmt, ... ) {
  va_list arg;
  va_start( arg, fmt );
  ParserTest::error_count++;
  va_end( arg );
  }
