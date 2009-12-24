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
  testFunctionDefinitionParsing();
  testBlockParsing();
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
  assert( !(int)(astMatchFunctionCall( &tokens )), "Matched a lone Identifier as a function call");

  // Match a identifier-leftparen-rightparen sequence
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, LeftParen, NULL);
  createToken( lastToken, RightParen, NULL);
  assert( (int)(newNode = astMatchFunctionCall( &tokens )), "Function-call token stream not matched as FunctionCall");
  assert( newNode->type == FunctionCall, "Function-call token stream not transformed into a FunctionCall AST-Node");
  
  // Don't match an identifier-rightparen sequence
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, RightParen, NULL );
  assert( !(int)(astMatchFunctionCall( &tokens )), "Matched a Identifier-RightParen sequence as a FunctionCall");

  // TODO: Function Call Parsing with parameters
  printf("\n");
}

void testFunctionParameterParsing() {
  Token *tokens, *lastToken;
  Node *newNode;
  
  printf( "- testFunctionParameterParsing");

  // Match a single string literal
  tokens = createToken( NULL, String, "Some string" );
  assert( (int)(newNode = astMatchParameter( &tokens )), "String literal token not matched as Parameter");
  assert( newNode->type == Parameter, "String literal not transformed into a Parameter AST-Node");
  assert( (int)(newNode->firstChild), "No child-node was attached to the Parameter AST-Node");
  assert( newNode->firstChild->type == StringLiteral, "Child node was not created as a StringLiteral AST-Node");

  // Match a single string literal
  tokens = createToken( NULL, Integer, "23212" );
  assert( (int)(newNode = astMatchParameter( &tokens )), "Integer literal token not matched as Parameter");
  assert( newNode->type == Parameter, "Integer literal not transformed into a Parameter AST-Node");
  assert( (int)(newNode->firstChild), "No child-node was attached to the Parameter AST-Node");
  assert( newNode->firstChild->type == IntegerLiteral, "Child node was not created as a IntegerLiteral AST-Node");
  
  // Should not match a single leftparen
  tokens = createToken( NULL, LeftParen, NULL );
  assert( !(int)astMatchParameter( &tokens ), "LeftParen token erroneously matched as Parameter AST-Node");

  // Should not match a single RightParen
  tokens = createToken( NULL, RightParen, NULL );
  assert( !(int)astMatchParameter( &tokens ), "RightParen token erroneously matched as Parameter AST-Node");

  // Should not match a single Colon
  tokens = createToken( NULL, Colon, NULL );
  assert( !(int)astMatchParameter( &tokens ), "Colon token erroneously matched as Parameter AST-Node");
  printf("\n");
}

void testFunctionDefinitionParsing() {
  Token *tokens, *lastToken, *savedToken;
  Node *newNode;

  printf("- testFunctionDefinitionParsing");

  // Should not match a lone parenthesis
  tokens = createToken( NULL, LeftParen, NULL );
  assert( !(int)astMatchFunctionDef( &tokens ), "LeftParen token erroneously matched as a FunctionDef AST-Node");

  // Should raise an error when a Lambda is not followed by a LeftParen
  tokens = createToken( NULL, Lambda, NULL);
  lastToken = createToken( tokens, RightParen, NULL);
  savedToken = tokens;
  assert( !(int)astMatchFunctionDef( &tokens ), "Lambda-RightParen token stream should not match as a FunctionDef AST-Node");
  tokens = savedToken;
  ASSERT_ERROR( astMatchFunctionDef( &tokens ));

  // Should not return a FunctionDefinitionNode for a Function def with no block
  tokens = createToken( NULL, Lambda, NULL);
  lastToken = createToken( tokens, LeftParen, NULL );
  lastToken = createToken( lastToken, RightParen, NULL );
  assert( !(int)(newNode = astMatchFunctionDef( &tokens )), "Lambda-etc with no block erroneously matched as a FunctionDef");
  
  // Should return a FunctionDefinition Node for Lambda-RightParen-LeftParen-Block
  tokens = createToken( NULL, Lambda, NULL);
  lastToken = createToken( tokens, LeftParen, NULL );
  lastToken = createToken( lastToken, RightParen, NULL );
  lastToken = createToken( lastToken, IndentIncrease, NULL);
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, NULL);
  lastToken = createToken( lastToken, String, "Blah");
  lastToken = createToken( lastToken, IndentDecrease, NULL);
  assert( (int)(newNode = astMatchFunctionDef( &tokens )), "Lambda-etc expected to match as a FunctionDef AST Node" );
  //assert( (newNode->type == FunctionDef), "Function Def token stream not matched as FunctionDef AST-Node");
  
  printf("\n");
}

void testBlockParsing() {
  Token *tokens, *lastToken, *savedToken;
  Node *newNode;

  printf("- testBlockParsing");

  // Should not match anything that doesn't start with an IndentIncrease
  tokens = createToken( NULL, IndentDecrease, NULL);
  assert( !(int)astMatchBlock( &tokens ), "IndentDecrease token erroneously matched as a block.");
 
  // Should not match an empty block
  tokens = createToken( NULL, IndentIncrease, NULL);
  createToken( tokens, IndentDecrease, NULL);
  assert( !(int)astMatchBlock( &tokens ), "IndentIncrease-Decrease erroneously matched as a block.");
  
  // Should match a block with an assignment
  tokens = createToken( NULL, IndentIncrease, NULL);
  lastToken = createToken( tokens, Identifier, "test");
  lastToken = createToken( lastToken, Equals, NULL);
  lastToken = createToken( lastToken, Integer, "123");
  lastToken = createToken( lastToken, IndentDecrease, NULL);
  assert( (int)(newNode = astMatchBlock( &tokens )), "Token stream not matched as Block AST-Node");
  //  assert( (int)(newNode->firstChild), "No child AST-Node generated for Block");
  printf("\n");
}
