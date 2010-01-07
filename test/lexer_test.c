#include <stdio.h>
#include <malloc.h>
#include "goat.h"
#include "lexer.h"
#include "test.h"

void LexerTest() {
  printf("Lexer Test\n");
  
  testTokenLexing();
  testFunctionLexing();
  testKeywordLexing();
  
  printf("\n");
}

void testFunctionLexing() {
  GoatState *G;
  Token *T;
  
  G = malloc(sizeof(GoatState));

  printf("- testFunctionLexing");  

  goatLexer(G, "test/function_test.gt");
  T = G->tokens;

  assert( T->type == Identifier, "First token was not an Identifier");
  T = T->next;

  assert( T->type == Equals, "Second token was not a Equals");
  T = T->next;

  assert( T->type == Lambda, "Third token was not a Lambda");
  T = T->next;

  assert( T->type == LeftParen, "Fourth token was not a RightParen");
  T = T->next;

  assert( T->type == Identifier, "Fifth token was not an Identifier");
  T = T->next;

  assert( T->type == RightParen, "Sixth token was not an LeftParen");
  T = T->next;

  assert( T->type == Newline, "Seventh token was not an Newline");
  T = T->next;
  
  assert( T->type == EndOfFile, "Eights token was not an EndOfFile");
  assert( T->next == NULL, "Unexpected nineth token found.");
  
  printf("\n");
  free(G);
}

void testTokenLexing() {
  GoatState *G;
  Token *T;
  
  G = malloc(sizeof(GoatState));

  printf("- testTokenLexing");  

  goatLexer(G, "test/token_test.gt");
  T = G->tokens;

  assert( T->type == LeftParen, "First token was not a LeftParen" );
  T = T->next;

  assert( T->type == RightParen, "Second token was not a RightParen" );
  T = T->next;

  assert( T->type == Colon, "Third Token was not a Colon" );
  T = T->next;

  assert( T->type == Equals, "Fourth token was not an Equals" );
  T = T->next;

  // The lexer should skip a comment here
  assert( T->type == Newline, "Fifth token was not a Newline");
  T = T->next;

  assert( T->type == Identifier, "Sixth token was not an Identifier" );
  T = T->next;

  assert( T->type == Period, "Seventh token was not a Period" );
  T = T->next;

  assert( T->type == Newline, "Eigthk token was not a newline");
  T = T->next;

  assert( T->type == IndentIncrease, "Nineth token was not an IndentIncrease" );
  T = T->next;

  assert( T->type == Identifier, "Tenth token was not an Identifier" );
  T = T->next;

  assert( T->type == Newline, "Eleventh token was not a Newline");
  T = T->next;

  assert( T->type == Integer, "Twelfth token was not an Integer" );
  T = T->next;

  assert( T->type == String, "Thirteenth token was not a String" );
  T = T->next;

  assert( T->type == Comma, "Fourteenth token was not a Comma" );
  T = T->next;

  assert( T->type == Newline, "Fourteenth token was not a Newline" );
  T = T->next;

  assert( T->type == IndentDecrease, "Fifteenth token was not an IndentDecrease" );
  T = T->next;

  assert( T->type == String, "Sixteenth token was not a String");
  T = T->next;

  assert( T->type == EndOfFile, "Seventeenth token was not an EndOfFile");
  assert( T->next == NULL, "Unexpected Eighteenth token found");

  printf("\n");
  free(G);
}

void testKeywordLexing() {
  GoatState *G;
  Token *T;
  
  G = malloc(sizeof(GoatState));

  printf("- testKeywordLexing");  

  goatLexer(G, "test/keywords.gt");
  T = G->tokens;  

  assert( T->type == If, "First token was not an If" );
  T = T->next;

  assert( T->type == Else, "Second token was not a Else" );
  T = T->next;

  assert( T->type == Class, "Third token was not a Class" );
  T = T->next;

  assert( T->type == Return, "Fourth token was not an Return" );
  T = T->next;
}
