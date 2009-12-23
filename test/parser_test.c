#include <stdio.h>
#include <malloc.h>
#include "goat.h"
#include "lexer.h"
#include "ast.h"
#include "test.h"

Token *createToken( Token*, enum TOKEN_TYPE, char*);

/* This is the "test suite" for the Parser test. It's role is simply
   to call each individual test in order */
void ParserTest() {
  printf("Parser Test\n");
  
  testExpressionParsing();
  testFunctionCallParsing();
  testFunctionParameterParsing();
  printf("\n");
}

/* Tests that the Expression matching rule only matches to an integer literal,
string literal, variable (i.e. identifier token), function call or function
definition */
void testExpressionParsing() {
  Token *tokens = NULL, *lastToken;
  Node *newNode = NULL;
  
  printf("- testExpressionParsing");

  tokens = createToken( NULL, String, "Test String");
  assert((int)(newNode = astMatchExpression( &tokens )), "String token not matched as Expression");
  assert(newNode->type == StringLiteral, "String token not made into a StringLiteral AST-Node");

  tokens = createToken( NULL, Integer, "123");
  assert((int)(newNode = astMatchExpression( &tokens )), "Integer token not matched as Expression");
  assert(newNode->type == IntegerLiteral, "Integer token not transformed into a IntegerLiteral AST-Node");

  tokens = createToken( NULL, Identifier, "variable_name");
  assert((int)(newNode = astMatchExpression( &tokens )), "Identifier token not matched as an Expression");
  assert(newNode->type == Variable, "Identifier token not transformed into a Variable AST-Node");

  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, RightParen, NULL );
  createToken( lastToken, LeftParen, NULL);

  assert((int)(newNode = astMatchExpression( &tokens )), "Function-call token stream not matched as an Expression");
  //assert(newNode->type == FunctionCall, "Function-call token stream not transformed into FunctionCall AST-Node");

  printf("\n");
}

void testFunctionCallParsing() {
  Token *tokens, *lastToken;
  Node *newNode;
  
  printf( "- testFunctionCallParsing");

  // Don't match a single identifier; that's a variable
  tokens = createToken( NULL, Identifier, "function_name");
  assert(!(int)(astMatchFunctionCall( &tokens )), "Matched a lone Identifier as a function call");

  // Match a identifier-leftparen-rightparen sequence
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, LeftParen, NULL);
  createToken( lastToken, RightParen, NULL);
  assert((int)(newNode = astMatchFunctionCall( &tokens )), "Function-call token stream not matched as FunctionCall");
  assert(newNode->type == FunctionCall, "Function-call token stream not transformed into a FunctionCall AST-Node");
  
  // Don't match an identifier-rightparen sequence
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, RightParen, NULL );
  assert(!(int)(astMatchFunctionCall( &tokens )), "Matched a Identifier-RightParen sequence as a FunctionCall");

  // TODO: Function Call Parsing with parameters
  printf("\n");
}

void testFunctionParameterParsing() {

}


