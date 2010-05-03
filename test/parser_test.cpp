#include <stdio.h>
#include <malloc.h>
#include <string>
#include "goat.h"
#include "lexer.h"
#include "ast_node.h"
#include "parser.h"
#include "test.h"

//Token *createToken( Token*, enum TOKEN_TYPE, std::string);
ASTNode *astMatchBlock( Token** );
ASTNode *astMatchStatement( Token** );
ASTNode *astMatchExpression( Token** );
ASTNode *astMatchMutableAssignment( Token** );
ASTNode *astMatchImmutableAssignment( Token** );
ASTNode *astMatchMethodInvocation( Token** );
ASTNode *astMatchFunctionCall( Token** );
ASTNode *astMatchParameter( Token ** );
ASTNode *astMatchFunctionDef( Token ** );
ASTNode *astMatchConditional( Token** );
ASTNode *astMatchClassDefinition( Token ** );
ASTNode *astMatchReturnStatement( Token ** );

Parser parser( NULL );

/* This is the "test suite" for the Parser test. It's role is simply
   to call each individual test in order */
ParserTest::ParserTest() {
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
  testClassDefinitionParsing();
  printf("\n");
}

void ParserTest::testStatementParsing() {
  Token *tokens = NULL, *lastToken;
  ASTNode *newNode = NULL;
  
  printf("- testStatementParsing");

  // Should match a immutable assignment as a statement
  tokens = createToken( NULL, Identifier, "var");
  lastToken = createToken( tokens, Colon, "");
  lastToken = createToken( lastToken, Integer, "123");

  assert((int)(newNode = astMatchStatement( &tokens )), "Immutable assignement token stream not match as a statement");
  assert(newNode->type == ASTNode::ImmutableAssignment, "Immutable assignement token stream not matched as ImmutableAssignment AST-Node");

  // Should match a immutable assignment as a statement
  tokens = createToken( NULL, Identifier, "var");
  lastToken = createToken( tokens, Equals, "");
  lastToken = createToken( lastToken, Integer, "123");

  assert((int)(newNode = astMatchStatement( &tokens )), "Mutable assignement token stream not match as a statement");
  assert(newNode->type == ASTNode::MutableAssignment, "Immutable assignement token stream not matched as MutableAssignment AST-Node");

  // Should match a function call as a statement
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, LeftParen, "");
  lastToken = createToken( lastToken, Integer, "1");
  lastToken = createToken( lastToken, RightParen, "");
  lastToken = createToken( lastToken, Newline, "");

  assert((int)(newNode = astMatchStatement( &tokens )), "Function call token stream not matched as a statement");
  assert(newNode->type == ASTNode::FunctionCall, "Function call token stream not matched as FunctionCall AST-Node");

  printf("\n");
}

/* Tests that the Expression matching rule only matches to an integer literal,
string literal, variable (i.e. identifier token), function call or function
definition */
void ParserTest::testExpressionParsing() {
  Token *tokens = NULL, *lastToken;
  ASTNode *newNode = NULL;
  
  printf("- testExpressionParsing");

  tokens = createToken( NULL, String, "Test String");
  assert((int)(newNode = astMatchExpression( &tokens )), "String token not matched as Expression");
  assert(newNode->type == ASTNode::StringLiteral, "String token not made into a StringLiteral AST-Node");

  tokens = createToken( NULL, Integer, "123");
  assert((int)(newNode = astMatchExpression( &tokens )), "Integer token not matched as Expression");
  assert(newNode->type == ASTNode::IntegerLiteral, "Integer token not transformed into a IntegerLiteral AST-Node");

  tokens = createToken( NULL, Identifier, "variable_name");
  assert((int)(newNode = astMatchExpression( &tokens )), "Identifier token not matched as an Expression");
  assert(newNode->type == ASTNode::Variable, "Identifier token not transformed into a Variable AST-Node");
  assert((int)newNode->token, "No token linked to the Variable AST-Node");

  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, RightParen, "");
  createToken( lastToken, LeftParen, "");

  assert((int)(newNode = astMatchExpression( &tokens )), "Function-call token stream not matched as an Expression");
  //assert(newNode->type == FunctionCall, "Function-call token stream not transformed into FunctionCall AST-Node");

  printf("\n");
}

void ParserTest::testMethodInvocationParsing() {
  Token *tokens, *lastToken;
  ASTNode *newNode;
  
  printf("- testMethodInvocationParsing");

  // Match a identifier-leftparen-rightparen sequence
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, LeftParen, "");
  lastToken = createToken( lastToken, RightParen, "");
  lastToken = createToken( lastToken, Newline, "");

  assert( (int)(newNode = astMatchMethodInvocation( &tokens )), "Function-call token stream not matched as FunctionCall");
  assert( newNode->type == ASTNode::FunctionCall, "Function-call token stream not transformed into a FunctionCall AST-Node");
  assert( newNode->firstChild == NULL, "Function call AST-Node has an illegitimate child.");  

  printf("\n");
}

void ParserTest::testFunctionCallParsing() {
  Token *tokens, *lastToken;
  ASTNode *newNode;
  
  printf( "- testFunctionCallParsing");

  // Don't match a single identifier; that's a variable
  tokens = createToken( NULL, Identifier, "function_name");
  assert( !(int)(astMatchFunctionCall( &tokens )), "Matched a lone Identifier as a function call");

  // Don't match an identifier-rightparen sequence
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, RightParen, "");
  assert( !(int)(astMatchFunctionCall( &tokens )), "Matched a Identifier-RightParen sequence as a FunctionCall");


  // Match a function call with parameters
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, LeftParen, "");
  lastToken = createToken( lastToken, String, "1");
  lastToken = createToken( lastToken, RightParen, "");

  assert( (int)(newNode = astMatchFunctionCall( &tokens )), "Function-call token stream not matched as FunctionCall");
  assert( newNode->type == ASTNode::FunctionCall, "Function-call token stream not transformed into a FunctionCall AST-Node");
  assert( (int) newNode->firstChild, "Function call AST-Node has no children with parameters");  

  // Match a function call with multiple parameters
  tokens = createToken( NULL, Identifier, "function_name");
  lastToken = createToken( tokens, LeftParen, "");
  lastToken = createToken( lastToken, String, "rah");
  lastToken = createToken( lastToken, Comma, "");
  lastToken = createToken( lastToken, Integer, "1");
  lastToken = createToken( lastToken, RightParen, "");

  assert( (int)(newNode = astMatchFunctionCall( &tokens )), "Function-call token stream not matched as FunctionCall");
  assert( newNode->type == ASTNode::FunctionCall, "Function-call token stream not transformed into a FunctionCall AST-Node");
  assert( (int) newNode->firstChild, "Function call AST-Node has no children with parameters");  
  printf("\n");
}

void ParserTest::testFunctionParameterParsing() {
  Token *tokens;
  ASTNode *newNode;
  
  printf( "- testFunctionParameterParsing");

  // Match a single string literal
  tokens = createToken( NULL, String, "Some string" );
  assert( (int)(newNode = astMatchParameter( &tokens )), "String literal token not matched as Parameter");
  assert( newNode->type == ASTNode::Parameter, "String literal not transformed into a Parameter AST-Node");
  assert( (int)(newNode->firstChild), "No child-node was attached to the Parameter AST-Node");
  assert( newNode->firstChild->type == ASTNode::StringLiteral, "Child node was not created as a StringLiteral AST-Node");

  // Match a single string literal
  tokens = createToken( NULL, Integer, "23212" );
  assert( (int)(newNode = astMatchParameter( &tokens )), "Integer literal token not matched as Parameter");
  assert( newNode->type == ASTNode::Parameter, "Integer literal not transformed into a Parameter AST-Node");
  assert( (int)(newNode->firstChild), "No child-node was attached to the Parameter AST-Node");
  assert( newNode->firstChild->type == ASTNode::IntegerLiteral, "Child node was not created as a IntegerLiteral AST-Node");
  
  // Should not match a single leftparen
  tokens = createToken( NULL, LeftParen, "");
  assert( !(int)astMatchParameter( &tokens ), "LeftParen token erroneously matched as Parameter AST-Node");

  // Should not match a single RightParen
  tokens = createToken( NULL, RightParen, "");
  assert( !(int)astMatchParameter( &tokens ), "RightParen token erroneously matched as Parameter AST-Node");

  // Should not match a single Colon
  tokens = createToken( NULL, Colon, "");
  assert( !(int)astMatchParameter( &tokens ), "Colon token erroneously matched as Parameter AST-Node");
  printf("\n");
}

void ParserTest::testFunctionDefinitionParsing() {
  Token *tokens, *lastToken, *savedToken;
  ASTNode *newNode;

  printf("- testFunctionDefinitionParsing");

  // Should not match a lone parenthesis
  tokens = createToken( NULL, LeftParen, "");
  assert( !(int)astMatchFunctionDef( &tokens ), "LeftParen token erroneously matched as a FunctionDef AST-Node");

  // Should raise an error when a Lambda is not followed by a LeftParen
  tokens = createToken( NULL, Lambda, "");
  lastToken = createToken( tokens, RightParen, "");
  savedToken = tokens;
  assert( !(int)astMatchFunctionDef( &tokens ), "Lambda-RightParen token stream should not match as a FunctionDef AST-Node");
  tokens = savedToken;
  ASSERT_ERROR( astMatchFunctionDef( &tokens ));

  // Should not return a FunctionDefinitionNode for a Function def with no block
  tokens = createToken( NULL, Lambda, "");
  lastToken = createToken( tokens, LeftParen, "");
  lastToken = createToken( lastToken, RightParen, "" );
  lastToken = createToken( lastToken, EndOfFile, "");
  assert( !(int)(newNode = astMatchFunctionDef( &tokens )), "Lambda-etc with no block erroneously matched as a FunctionDef");
  
  // Should return a FunctionDefinition Node for Lambda-RightParen-LeftParen-Block
  tokens = createToken( NULL, Lambda, "");
  lastToken = createToken( tokens, LeftParen, "");
  lastToken = createToken( lastToken, RightParen, "" );
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentIncrease, "");
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, "");
  lastToken = createToken( lastToken, String, "Blah");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentDecrease, "");
  assert( (int)(newNode = astMatchFunctionDef( &tokens )), "Lambda-etc expected to match as a FunctionDef AST Node" );
  assert( (newNode->type == ASTNode::FunctionDef), "Function Def token stream not matched as FunctionDef AST-Node");
  
  // Should return a FunctionDefinition Node for a Function with a single parameter
  tokens = createToken( NULL, Lambda, "");
  lastToken = createToken( tokens, LeftParen, "");
  lastToken = createToken( lastToken, Identifier, "a");
  lastToken = createToken( lastToken, RightParen, "" );
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentIncrease, "");
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, "");
  lastToken = createToken( lastToken, String, "Blah");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentDecrease, "");
  assert( (int)(newNode = astMatchFunctionDef( &tokens )), "Lambda-etc with single paramater expected to match as a FunctionDef AST Node" );

  // Should return a FunctionDefinition Node for a Function with multiple parameters
  tokens = createToken( NULL, Lambda, "");
  lastToken = createToken( tokens, LeftParen, "" );
  lastToken = createToken( lastToken, Identifier, "a");
  lastToken = createToken( lastToken, Comma, "");
  lastToken = createToken( lastToken, Identifier, "b");
  lastToken = createToken( lastToken, RightParen, "" );
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentIncrease, "");
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, "");
  lastToken = createToken( lastToken, String, "Blah");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentDecrease, "");
  assert( (int)(newNode = astMatchFunctionDef( &tokens )), "Lambda-etc with multiple paramaters expected to match as a FunctionDef AST Node" );
  //assert( (newNode->type == FunctionDef), "Function Def token stream not matched as FunctionDef AST-Node");
  printf("\n");
}

void ParserTest::testBlockParsing() {
  Token *tokens, *lastToken;
  ASTNode *newNode;

  printf("- testBlockParsing");

  // Should not match anything that doesn't start with an IndentIncrease
  tokens = createToken( NULL, IndentDecrease, "");
  assert( !(int)astMatchBlock( &tokens ), "IndentDecrease token erroneously matched as a block.");
 
  // Should not match an empty block
  tokens = createToken( NULL, IndentIncrease, "");
  createToken( tokens, IndentDecrease, "");
  assert( !(int)astMatchBlock( &tokens ), "IndentIncrease-Decrease erroneously matched as a block.");
  
  // Should match a block with an assignment
  tokens = createToken( NULL, IndentIncrease, "");
  lastToken = createToken( tokens, Identifier, "test");
  lastToken = createToken( lastToken, Equals, "");
  lastToken = createToken( lastToken, Integer, "123");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentDecrease, "");
  assert( (int)(newNode = astMatchBlock( &tokens )), "Token stream not matched as Block AST-Node");
  //  assert( (int)(newNode->firstChild), "No child AST-Node generated for Block");
  printf("\n");
}

void ParserTest::testMutableAssignmentParsing() {
  Token *tokens, *lastToken;
  ASTNode *newNode;

  printf("- testMutableAssignmentParsing");

  tokens = createToken( NULL, Identifier, "var");
  lastToken = createToken( tokens, Equals, "");
  lastToken = createToken( lastToken, Integer, "123");

  assert((int)(newNode = astMatchMutableAssignment( &tokens )), "Mutable assignment token stream not matched as AST-Node");
  assert(newNode->type == ASTNode::MutableAssignment, "Mutable assignment token stream not matched as a MutableAssignment AST-Node");
  assert((int)newNode->token, "No token assigned to new MutableAssignemnt AST-Node");
  assert((int)(newNode->firstChild), "MutableAssignment AST-Node has no children");
  assert(newNode->firstChild->type == ASTNode::IntegerLiteral, "MutableAssignment AST-Node not a IntegerLiteral");

  
  printf("\n");
}

void ParserTest::testImmutableAssignmentParsing() {
  Token *tokens, *lastToken;
  ASTNode *newNode;

  printf("- testImmutableAssignmentParsing");

  tokens = createToken( NULL, Identifier, "var");
  lastToken = createToken( tokens, Colon, "");
  lastToken = createToken( lastToken, Integer, "123");

  assert((int)(newNode = astMatchImmutableAssignment( &tokens )), "Immutable assignment token stream not matched as AST-Node");
  assert(newNode->type == ASTNode::ImmutableAssignment, "Immutable assignment token stream not matched as a MutableAssignment AST-Node");
  assert((int)newNode->token, "No token assigned to new ImutableAssignment AST-Node");
  assert((int)(newNode->firstChild), "ImmutableAssignment AST-Node has no children");
  assert(newNode->firstChild->type == ASTNode::IntegerLiteral, "ImmutableAssignment AST-Node not a IntegerLiteral");

  
  printf("\n");
}

void ParserTest::testConditionalParsing() {
  Token *tokens, *lastToken;
  ASTNode *newNode;

  printf("- testConditionalParsing");
  // Don't match anything that doesn't start with an If token
  tokens = createToken( NULL, Else, "");
  assert(!(int)astMatchConditional( &tokens ), "Else-token incorrectly matched as a Conditional AST-Node");
  
  // Test parsing of a block with only an if clause
  tokens = createToken( NULL, If, "");
  lastToken = createToken( tokens, Identifier, "blah");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentIncrease, "");
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, "");
  lastToken = createToken( lastToken, Integer, "23");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentDecrease, "");

  assert((int)(newNode = astMatchConditional( &tokens )), "Conditional token stream not matched as Conditional AST node" );
  assert(newNode->type == ASTNode::Conditional, "Conditional token stream not matched as a Conditional-type AST-Node");
  assert((int)newNode->firstChild, "Conditional AST-Node has no children nodes");
  assert(newNode->firstChild->type == ASTNode::Variable, "First child-node was not a Variable type");
  assert((int)newNode->firstChild->nextSibling, "Conditional AST-Node hasn't a second child node");
  assert(newNode->firstChild->nextSibling->type == ASTNode::Block, "Conditional AST-Node's second child not a Block");

  // Test parsing of a block with only an if and an else clause
  tokens = createToken( NULL, If, "");
  lastToken = createToken( tokens, Identifier, "blah");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentIncrease, "");
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, "");
  lastToken = createToken( lastToken, Integer, "23");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentDecrease, "");
  lastToken = createToken( lastToken, Else, "");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentIncrease, "");
  lastToken = createToken( lastToken, Identifier, "function");
  lastToken = createToken( lastToken, LeftParen, "");
  lastToken = createToken( lastToken, RightParen, "");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentDecrease, "");

  assert((int)(newNode = astMatchConditional( &tokens )), "Conditional token stream not matched as Conditional AST node" );
  assert(newNode->type == ASTNode::Conditional, "Conditional token stream not matched as a Conditional-type AST-Node");
  assert((int)newNode->firstChild, "Conditional AST-Node has no children nodes");
  assert(newNode->firstChild->type == ASTNode::Variable, "First child-node was not a Variable type");
  assert((int)newNode->firstChild->nextSibling, "Conditional AST-Node hasn't a second child node");
  assert(newNode->firstChild->nextSibling->type == ASTNode::Block, "Conditional AST-Node's second child not a Block");
  assert((int)newNode->firstChild->nextSibling->nextSibling, "No third child AST-Node found for else clause");
  assert(newNode->firstChild->nextSibling->nextSibling->type == ASTNode::Block, "Third child AST-Node was not a Block");

  // Should not match a condition block with an Else token but no statement
  tokens = createToken( NULL, If, "");
  lastToken = createToken( tokens, Identifier, "blah");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentIncrease, "");
  lastToken = createToken( lastToken, Identifier, "var");
  lastToken = createToken( lastToken, Equals, "");
  lastToken = createToken( lastToken, Integer, "23");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentDecrease, "");
  lastToken = createToken( lastToken, Else, "");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, Identifier, "function");
  lastToken = createToken( lastToken, LeftParen, "");
  lastToken = createToken( lastToken, RightParen, "");
  lastToken = createToken( lastToken, Newline, "");

  assert(!(int)astMatchConditional( &tokens ), "Conditional block with missing else clause matched as block");
  ASSERT_ERROR(astMatchConditional( &tokens ));
  printf("\n");
  
}

void ParserTest::testReturnParsing() {
  Token *tokens, *lastToken;  
  ASTNode *newNode;

  printf("- testReturnParsing");

  // Should not match a statement which doesn't start with a return
  tokens = createToken( NULL, If, "");
  createToken( tokens, Integer, "123");

  assert(!(int)astMatchReturnStatement( &tokens ), "If-token erroneously matched as a ReturnStatement AST-Node");

  // Should match return token, followed by an expression
  tokens = createToken( NULL, Return, "");
  lastToken = createToken( tokens, Identifier, "a");
  lastToken = createToken( lastToken, Identifier, "+");
  lastToken = createToken( lastToken, Identifier, "b");

  assert((int)(newNode = astMatchReturnStatement( &tokens )), "ReturnStatement token stream not matched as ReturnStatement AST-Node");
  assert(newNode->type == ASTNode::ReturnStatement, "ReturnStatement token stream Node not of ReturnStatement type.");
  assert((int)newNode->firstChild, "ReturnStatement AST-Node has no child AST-Node");

  assert(newNode->firstChild->type == ASTNode::FunctionCall, "ReturnStatement child AST-Node not matched as a function call");

  // Should match a return token, with no return expression (but replace that with a NullLiteral)
  tokens = createToken( NULL, Return, "");
  lastToken = createToken( tokens, Newline, "");

  assert((int)(newNode = astMatchReturnStatement( &tokens )), "ReturnStatement token stream not matched as ReturnStatement AST-Node");
  assert(newNode->type == ASTNode::ReturnStatement, "ReturnStatement token stream Node not of ReturnStatement type.");
  assert((int)newNode->firstChild, "ReturnStatement AST-Node has no child AST-Node");
  assert(newNode->firstChild->type == ASTNode::NullLiteral, "ReturnStatement child AST-Node not generated with a NullLiteral child");

  printf("\n");
}

void ParserTest::testClassDefinitionParsing() {
  Token *tokens, *lastToken;
  ASTNode *newNode;

  printf("- testClassDefinitionParsing");

  // Should not match anything that doesn't start with the class keyword
  tokens = createToken( NULL, Identifier, "");
  createToken( tokens, Newline, "");
  assert(!astMatchClassDefinition( &tokens ), "Identifier erroneously matched as a Class Definition");

  // Should not match a class name without an identifier naming it.
  tokens = createToken( NULL, Class, "");
  createToken( tokens, RightParen, "");
  ASSERT_ERROR((newNode = astMatchClassDefinition( &tokens )));
  assert(!newNode, "Class-RightParen erroneously matched as a Class Definition");

  // Should match an empty class
  tokens = createToken( NULL, Class, "");
  lastToken = createToken( tokens, Identifier, "Integer");
  createToken( lastToken, Newline, "");
  assert((int)(newNode = astMatchClassDefinition( &tokens )), "Class-Identifier not matched as a ClassDefinition AST-Node");
  assert(newNode->type == ASTNode::ClassDefinition, "Class-Identifier not matched as a ClassDefinition AST-Node");
  assert((int)newNode->token, "ClassDefinition AST-Node has not linked Token");

  // Should match a class with an assignment
  tokens = createToken( NULL, Class, "");
  lastToken = createToken( tokens, Identifier, "Integer");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentIncrease, "");
  lastToken = createToken( lastToken, Identifier, "value");
  lastToken = createToken( lastToken, Colon, "");
  lastToken = createToken( lastToken, Integer, "123");
  lastToken = createToken( lastToken, Newline, "");
  lastToken = createToken( lastToken, IndentDecrease, "");
  assert((int)(newNode = astMatchClassDefinition( &tokens )), "Class with assignment in block not matched as a ClassDefinition AST-Node");
  
  printf("\n");
}

ASTNode *astMatchBlock( Token** tokens ) {
  parser = Parser( *tokens );
  return parser.MatchBlock();
}

ASTNode *astMatchStatement( Token** tokens ) {
  Parser p = Parser( *tokens );
  return p.MatchStatement();
}

ASTNode *astMatchExpression( Token** tokens ) {
  parser = Parser( *tokens );
  return parser.MatchExpression();
}

ASTNode *astMatchMutableAssignment( Token** tokens ) {
  parser = Parser( *tokens );
  return parser.MatchMutableAssignment();
}

ASTNode *astMatchImmutableAssignment( Token** tokens ) {
  parser = Parser( *tokens );
  return parser.MatchImmutableAssignment();
}

ASTNode *astMatchMethodInvocation( Token **tokens ) {
  parser = Parser( *tokens );
  return parser.MatchMethodInvocation();
}

ASTNode *astMatchFunctionCall( Token **tokens ) {
  parser = Parser( *tokens );
  return parser.MatchFunctionCall();
}

ASTNode *astMatchParameter( Token **tokens ) {
  parser = Parser( *tokens );
  return parser.MatchParameter();
}

ASTNode *astMatchFunctionDef( Token **tokens ) {
  parser = Parser( *tokens );
  return parser.MatchFunctionDef();
}

ASTNode *astMatchConditional( Token **tokens ) {
  parser = Parser( *tokens );
  return parser.MatchConditional();
}

ASTNode *astMatchReturnStatement( Token **tokens ) {
  parser = Parser( *tokens );
  return parser.MatchReturnStatement();
}

ASTNode *astMatchClassDefinition( Token **tokens ) {
  parser = Parser( *tokens );
  return parser.MatchClassDefinition();
}
