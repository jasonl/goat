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

  testBlockParsing();
  testStatementParsing();
  testExpressionParsing();
  testMethodInvocationParsing();
  testFunctionCallParsing();
  testFunctionParameterParsing();
  testFunctionDefinitionParsing();
  testMutableAssignmentParsing();
  testImmutableAssignmentParsing();
  testConditionalParsing();
  testReturnParsing();

  printf("\n");
}

void testStatementParsing() {
  Token *tokens = NULL, *lastToken;
  Node *newNode = NULL;
  
  printf("- testStatementParsing");

  // Should match a immutable assignment as a statement
  tokens = createToken( NULL, Identifier, "var");
  lastToken = createToken( tokens, Colon, NULL);
  lastToken = createToken( lastToken, Integer, "123");

  assert((int)(newNode = astMatchStatement( &tokens )), "Immutable assignement token stream not match as a statement");
  assert(newNode->type == ImmutableAssignment, "Immutable assignement token stream not matched as ImmutableAssignment AST-Node");

  // Should match a immutable assignment as a statement
  tokens = createToken( NULL, Identifier, "var");
  lastToken = createToken( tokens, Equals, NULL);
  lastToken = createToken( lastToken, Integer, "123");

  assert((int)(newNode = astMatchStatement( &tokens )), "Mutable assignement token stream not match as a statement");
  assert(newNode->type == MutableAssignment, "Immutable assignement token stream not matched as MutableAssignment AST-Node");

  // Should match a function call as a statement
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, LeftParen, NULL);
  lastToken = createToken( lastToken, Integer, "1");
  lastToken = createToken( lastToken, RightParen, NULL);
  lastToken = createToken( lastToken, Newline, NULL);

  assert((int)(newNode = astMatchStatement( &tokens )), "Function call token stream not matched as a statement");
  assert(newNode->type == FunctionCall, "Function call token stream not matched as FunctionCall AST-Node");

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
  assert((int)newNode->token, "No token linked to the Variable AST-Node");

  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, RightParen, NULL );
  createToken( lastToken, LeftParen, NULL);

  assert((int)(newNode = astMatchExpression( &tokens )), "Function-call token stream not matched as an Expression");
  //assert(newNode->type == FunctionCall, "Function-call token stream not transformed into FunctionCall AST-Node");

  printf("\n");
}

void testMethodInvocationParsing() {
  Token *tokens, *lastToken;
  Node *newNode;
  
  printf("- testMethodInvocationParsing");

  // Match a identifier-leftparen-rightparen sequence
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, LeftParen, NULL);
  lastToken = createToken( lastToken, RightParen, NULL);
  lastToken = createToken( lastToken, Newline, NULL);

  assert( (int)(newNode = astMatchMethodInvocation( &tokens )), "Function-call token stream not matched as FunctionCall");
  assert( newNode->type == FunctionCall, "Function-call token stream not transformed into a FunctionCall AST-Node");
  assert( newNode->firstChild == NULL, "Function call AST-Node has an illegitimate child.");  

  printf("\n");
}

void testFunctionCallParsing() {
  Token *tokens, *lastToken;
  Node *newNode;
  
  printf( "- testFunctionCallParsing");

  // Don't match a single identifier; that's a variable
  tokens = createToken( NULL, Identifier, "function_name");
  assert( !(int)(astMatchFunctionCall( &tokens )), "Matched a lone Identifier as a function call");

  // Don't match an identifier-rightparen sequence
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, RightParen, NULL );
  assert( !(int)(astMatchFunctionCall( &tokens )), "Matched a Identifier-RightParen sequence as a FunctionCall");


  // Match a function call with parameters
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, LeftParen, NULL);
  lastToken = createToken( lastToken, String, "1");
  lastToken = createToken( lastToken, RightParen, NULL);

  assert( (int)(newNode = astMatchFunctionCall( &tokens )), "Function-call token stream not matched as FunctionCall");
  assert( newNode->type == FunctionCall, "Function-call token stream not transformed into a FunctionCall AST-Node");
  assert( (int) newNode->firstChild, "Function call AST-Node has no children with parameters");  

  // Match a function call with multiple parameters
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, LeftParen, NULL);
  lastToken = createToken( lastToken, String, "rah");
  lastToken = createToken( lastToken, Comma, NULL);
  lastToken = createToken( lastToken, Integer, "1");
  lastToken = createToken( lastToken, RightParen, NULL);

  assert( (int)(newNode = astMatchFunctionCall( &tokens )), "Function-call token stream not matched as FunctionCall");
  assert( newNode->type == FunctionCall, "Function-call token stream not transformed into a FunctionCall AST-Node");
  assert( (int) newNode->firstChild, "Function call AST-Node has no children with parameters");  
  printf("\n");
}

void testFunctionParameterParsing() {
  Token *tokens;
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
  lastToken = createToken( lastToken, EndOfFile, NULL);
  assert( !(int)(newNode = astMatchFunctionDef( &tokens )), "Lambda-etc with no block erroneously matched as a FunctionDef");
  
  // Should return a FunctionDefinition Node for Lambda-RightParen-LeftParen-Block
  tokens = createToken( NULL, Lambda, NULL);
  lastToken = createToken( tokens, LeftParen, NULL );
  lastToken = createToken( lastToken, RightParen, NULL );
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentIncrease, NULL);
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, NULL);
  lastToken = createToken( lastToken, String, "Blah");
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentDecrease, NULL);
  assert( (int)(newNode = astMatchFunctionDef( &tokens )), "Lambda-etc expected to match as a FunctionDef AST Node" );
  assert( (newNode->type == FunctionDef), "Function Def token stream not matched as FunctionDef AST-Node");
  
  // Should return a FunctionDefinition Node for a Function with a single parameter
  tokens = createToken( NULL, Lambda, NULL);
  lastToken = createToken( tokens, LeftParen, NULL );
  lastToken = createToken( lastToken, Identifier, "a");
  lastToken = createToken( lastToken, RightParen, NULL );
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentIncrease, NULL);
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, NULL);
  lastToken = createToken( lastToken, String, "Blah");
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentDecrease, NULL);
  assert( (int)(newNode = astMatchFunctionDef( &tokens )), "Lambda-etc with single paramater expected to match as a FunctionDef AST Node" );

  // Should return a FunctionDefinition Node for a Function with multiple parameters
  tokens = createToken( NULL, Lambda, NULL);
  lastToken = createToken( tokens, LeftParen, NULL );
  lastToken = createToken( lastToken, Identifier, "a");
  lastToken = createToken( lastToken, Comma, NULL);
  lastToken = createToken( lastToken, Identifier, "b");
  lastToken = createToken( lastToken, RightParen, NULL );
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentIncrease, NULL);
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, NULL);
  lastToken = createToken( lastToken, String, "Blah");
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentDecrease, NULL);
  assert( (int)(newNode = astMatchFunctionDef( &tokens )), "Lambda-etc with multiple paramaters expected to match as a FunctionDef AST Node" );
  //assert( (newNode->type == FunctionDef), "Function Def token stream not matched as FunctionDef AST-Node");
  printf("\n");
}

void testBlockParsing() {
  Token *tokens, *lastToken;
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
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentDecrease, NULL);
  assert( (int)(newNode = astMatchBlock( &tokens )), "Token stream not matched as Block AST-Node");
  //  assert( (int)(newNode->firstChild), "No child AST-Node generated for Block");
  printf("\n");
}

void testMutableAssignmentParsing() {
  Token *tokens, *lastToken;
  Node *newNode;

  printf("- testMutableAssignmentParsing");

  tokens = createToken( NULL, Identifier, "var");
  lastToken = createToken( tokens, Equals, NULL);
  lastToken = createToken( lastToken, Integer, "123");

  assert((int)(newNode = astMatchMutableAssignment( &tokens )), "Mutable assignment token stream not matched as AST-Node");
  assert(newNode->type == MutableAssignment, "Mutable assignment token stream not matched as a MutableAssignment AST-Node");
  assert((int)newNode->token, "No token assigned to new MutableAssignemnt AST-Node");
  assert((int)(newNode->firstChild), "MutableAssignment AST-Node has no children");
  assert(newNode->firstChild->type == IntegerLiteral, "MutableAssignment AST-Node not a IntegerLiteral");

  
  printf("\n");
}

void testImmutableAssignmentParsing() {
  Token *tokens, *lastToken;
  Node *newNode;

  printf("- testImmutableAssignmentParsing");

  tokens = createToken( NULL, Identifier, "var");
  lastToken = createToken( tokens, Colon, NULL);
  lastToken = createToken( lastToken, Integer, "123");

  assert((int)(newNode = astMatchImmutableAssignment( &tokens )), "Immutable assignment token stream not matched as AST-Node");
  assert(newNode->type == ImmutableAssignment, "Immutable assignment token stream not matched as a MutableAssignment AST-Node");
  assert((int)newNode->token, "No token assigned to new ImutableAssignment AST-Node");
  assert((int)(newNode->firstChild), "ImmutableAssignment AST-Node has no children");
  assert(newNode->firstChild->type == IntegerLiteral, "ImmutableAssignment AST-Node not a IntegerLiteral");

  
  printf("\n");
}

void testConditionalParsing() {
  Token *tokens, *lastToken;
  Node *newNode;

  printf("- testConditionalParsing");
  // Don't match anything that doesn't start with an If token
  tokens = createToken( NULL, Else, NULL );
  assert(!(int)astMatchConditional( &tokens ), "Else-token incorrectly matched as a Conditional AST-Node");
  
  // Test parsing of a block with only an if clause
  tokens = createToken( NULL, If, NULL);
  lastToken = createToken( tokens, Identifier, "blah");
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentIncrease, NULL);
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, NULL);
  lastToken = createToken( lastToken, Integer, "23");
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentDecrease, NULL);

  assert((int)(newNode = astMatchConditional( &tokens )), "Conditional token stream not matched as Conditional AST node" );
  assert(newNode->type == Conditional, "Conditional token stream not matched as a Conditional-type AST-Node");
  assert((int)newNode->firstChild, "Conditional AST-Node has no children nodes");
  assert(newNode->firstChild->type == Variable, "First child-node was not a Variable type");
  assert((int)newNode->firstChild->nextSibling, "Conditional AST-Node hasn't a second child node");
  assert(newNode->firstChild->nextSibling->type == Block, "Conditional AST-Node's second child not a Block");

  // Test parsing of a block with only an if and an else clause
  tokens = createToken( NULL, If, NULL);
  lastToken = createToken( tokens, Identifier, "blah");
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentIncrease, NULL);
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, NULL);
  lastToken = createToken( lastToken, Integer, "23");
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentDecrease, NULL);
  lastToken = createToken( lastToken, Else, NULL);
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentIncrease, NULL);
  lastToken = createToken( lastToken, Identifier, "function");
  lastToken = createToken( lastToken, LeftParen, NULL);
  lastToken = createToken( lastToken, RightParen, NULL);
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentDecrease, NULL);

  assert((int)(newNode = astMatchConditional( &tokens )), "Conditional token stream not matched as Conditional AST node" );
  assert(newNode->type == Conditional, "Conditional token stream not matched as a Conditional-type AST-Node");
  assert((int)newNode->firstChild, "Conditional AST-Node has no children nodes");
  assert(newNode->firstChild->type == Variable, "First child-node was not a Variable type");
  assert((int)newNode->firstChild->nextSibling, "Conditional AST-Node hasn't a second child node");
  assert(newNode->firstChild->nextSibling->type == Block, "Conditional AST-Node's second child not a Block");
  assert((int)newNode->firstChild->nextSibling->nextSibling, "No third child AST-Node found for else clause");
  assert(newNode->firstChild->nextSibling->nextSibling->type == Block, "Third child AST-Node was not a Block");

  // Should not match a condition block with an Else token but no statement
  tokens = createToken( NULL, If, NULL);
  lastToken = createToken( tokens, Identifier, "blah");
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentIncrease, NULL);
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, NULL);
  lastToken = createToken( lastToken, Integer, "23");
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, IndentDecrease, NULL);
  lastToken = createToken( lastToken, Else, NULL);
  lastToken = createToken( lastToken, Newline, NULL);
  lastToken = createToken( lastToken, Identifier, "function");
  lastToken = createToken( lastToken, LeftParen, NULL);
  lastToken = createToken( lastToken, RightParen, NULL);
  lastToken = createToken( lastToken, Newline, NULL);

  assert(!(int)astMatchConditional( &tokens ), "Conditional block with missing else clause matched as block");
  ASSERT_ERROR(astMatchConditional( &tokens ));
  printf("\n");
  
}

void testReturnParsing() {
  Token *tokens, *lastToken;  
  Node *newNode;

  printf("- testReturnParsing");

  // Should not match a statement which doesn't start with a return
  tokens = createToken( NULL, If, NULL);
  createToken( tokens, Integer, "123");

  assert(!(int)astMatchReturnStatement( &tokens ), "If-token erroneously matched as a ReturnStatement AST-Node");

  // Should match return token, followed by an expression
  tokens = createToken( NULL, Return, NULL);
  lastToken = createToken( tokens, Identifier, "a");
  lastToken = createToken( tokens, Identifier, "+");
  lastToken = createToken( tokens, Identifier, "b");

  assert((int)(newNode = astMatchReturnStatement( &tokens )), "ReturnStatement token stream not matched as ReturnStatement AST-Node");
  assert(newNode->type == ReturnStatement, "ReturnStatement token stream Node not of ReturnStatement type.");
  assert((int)newNode->firstChild, "ReturnStatement AST-Node has no child AST-Node");
  assert(newNode->firstChild->type == FunctionCall, "ReturnStatement child AST-Node not matched as a function call");

  // Should match a return token, with no return expression (but replace that with a NullLiteral)
  tokens = createToken( NULL, Return, NULL);
  lastToken = createToken( tokens, Newline, NULL);

  assert((int)(newNode = astMatchReturnStatement( &tokens )), "ReturnStatement token stream not matched as ReturnStatement AST-Node");
  assert(newNode->type == ReturnStatement, "ReturnStatement token stream Node not of ReturnStatement type.");
  assert((int)newNode->firstChild, "ReturnStatement AST-Node has no child AST-Node");
  assert(newNode->firstChild->type == NullLiteral, "ReturnStatement child AST-Node not generated with a NullLiteral child");

  printf("\n");
}
