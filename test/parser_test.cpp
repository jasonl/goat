#include <gtest/gtest.h>
#include "token.hpp"
#include "ast_node.h"
#include "parser.h"

typedef std::list<Token>::iterator TokenIterator;

namespace {
  class ParserTest : public ::testing::Test {
  protected:
    void Add( TokenType _type, std::string _content = "" ) { 
      tokenStream.push_back( Token( _type, _content ) );
    }
    std::list<Token> tokenStream;
  };

  // Tests correct parsing of an immutable assignement as statement
  TEST_F( ParserTest, ShouldMatchImmutableAssignmentAsStatement ) {
    Add( Identifier, "var"); Add( Colon ); Add( Integer, "123" );
    ASTNode* immutable = Parser( tokenStream ).MatchStatement();
    EXPECT_EQ( ASTNode::ImmutableAssignment, immutable->Type() );
  }

  // Tests correct parsing of a mutable assignment as a statement
  TEST_F( ParserTest, ShouldMatchMutableAssignmentAsStatement ) {
    Add( Identifier, "var"); Add( Equals ); Add( Integer, "123" );
    ASTNode* _mutable = Parser( tokenStream ).MatchStatement();
    EXPECT_EQ( ASTNode::MutableAssignment, _mutable->Type() );
  }

  // Tests correct parsing of a function call as a statement
  TEST_F( ParserTest, ShouldMatchFunctionCallAsStatement ) {
    Add( Identifier, "function_name" );
    Add( LeftParen ); Add( Integer, "1" ); Add( RightParen );
    Add( Newline );
    ASTNode* functionCall = Parser( tokenStream ).MatchStatement();
    EXPECT_EQ( ASTNode::FunctionCall, functionCall->Type() );
  }

  // Tests a string literal is parsed as an expression
  TEST_F( ParserTest, ShouldMatchStringLiteralAsExpression ) {
    Add( String, "Some String" );
    ASTNode* stringLiteral = Parser( tokenStream ).MatchExpression();
    EXPECT_EQ( ASTNode::StringLiteral, stringLiteral->Type() );
    EXPECT_EQ( "Some String", stringLiteral->Content() );
  }

  // Tests a integer literal is parsed as an expression
  TEST_F( ParserTest, ShouldMatchIntegerLiteralAsExpression ) {
    Add( Integer, "12345" );
    ASTNode* integerLiteral = Parser( tokenStream ).MatchExpression();
    EXPECT_EQ( ASTNode::IntegerLiteral, integerLiteral->Type() );
    EXPECT_EQ( "12345", integerLiteral->Content() );
  }

  // Tests a variable is parsed as an expression
  TEST_F( ParserTest, ShouldMatchVariableAsExpression ) {
    Add( Identifier, "var_name" );
    ASTNode* variable = Parser( tokenStream ).MatchExpression();
    EXPECT_EQ( ASTNode::Variable, variable->Type() );
    EXPECT_EQ( "var_name", variable->Content() );
  }

  // Tests a function call is parsed as an expression
  TEST_F( ParserTest, ShouldMatchFunctionCallAsExpression ) {
    Add( Identifier, "function_name");
    Add( LeftParen ); Add( RightParen );
    ASTNode *functionCall = Parser( tokenStream ).MatchExpression();
    EXPECT_EQ( ASTNode::FunctionCall, functionCall->Type() );
    EXPECT_EQ( "function_name", functionCall->Content() );
  }

  TEST_F( ParserTest, ShouldMatchMethodInvocation ) {
    Add( Identifier, "function_name" );
    Add( LeftParen ); Add( RightParen ); 
    ASTNode *functionCall = Parser( tokenStream ).MatchMethodInvocation();
    EXPECT_EQ( ASTNode::FunctionCall, functionCall->Type() );
    EXPECT_EQ( "function_name", functionCall->Content() );
  }

  // Tests that the parser doesn't match a single identifier without 
  // parentheses following as a function call. It's the job of
  // semantic analysis to translate this if required, not the parser.
  TEST_F( ParserTest, ShouldntMatchSingleIdentifierAsFunctionCall ) {
    Add( Identifier, "function_name" );
    ASTNode *functionCall = Parser( tokenStream ).MatchFunctionCall();
    EXPECT_EQ( NULL, functionCall );
  }

  TEST_F( ParserTest, ShouldntMatchMalformedFunctionCall ) {
    Add( Identifier, "function_name" );
    Add( RightParen );
    ASTNode *functionCall = Parser( tokenStream ).MatchFunctionCall();
    EXPECT_EQ( NULL, functionCall );
  }
  
  TEST_F( ParserTest, ShouldMatchAFunctionCallWithParameters ) {
    Add( Identifier, "function_name"); Add( LeftParen );
    Add( Integer, "1" ); Add( RightParen );
    ASTNode *functionCall = Parser( tokenStream ).MatchFunctionCall();
    EXPECT_EQ( ASTNode::FunctionCall, functionCall->Type() );
    EXPECT_EQ( "function_name", functionCall->Content() );
  }

  TEST_F( ParserTest, ShouldMatchFunctionCallMultipleParams ) {
    Add( Identifier, "function_name" ); Add( LeftParen );
    Add( Integer, "1" ); Add( Comma );
    Add( String, "abc" ); Add( RightParen );
    ASTNode *functionCall = Parser( tokenStream ).MatchFunctionCall();
    EXPECT_EQ( ASTNode::FunctionCall, functionCall->Type() );
    EXPECT_EQ( "function_name", functionCall->Content() );

    ASTIterator params = functionCall->ChildNodes();
    EXPECT_EQ( ASTNode::Parameter, params->Type() );
    EXPECT_EQ( ASTNode::Parameter, (++params)->Type() );
  }

  // Test that a String Literal is matched as a Parameter
  TEST_F( ParserTest, ShouldMatchStringLiteralAsParameter ) {
    Add( String, "Some String");
    ASTNode *parameter = Parser( tokenStream ).MatchParameter();
    EXPECT_EQ( ASTNode::Parameter, parameter->Type() );
    
    ASTIterator nodes = parameter->ChildNodes();
    EXPECT_EQ( ASTNode::StringLiteral, nodes->Type() );
    EXPECT_EQ( "Some String", nodes->Content() );
  }

  // Test that a Integer Literal is matched as a Parameter
  TEST_F( ParserTest, ShouldMatchIntegerLiteralAsParameter ) {
    Add( Integer, "432");
    ASTNode *parameter = Parser( tokenStream ).MatchParameter();
    EXPECT_EQ( ASTNode::Parameter, parameter->Type() );
    
    ASTIterator nodes = parameter->ChildNodes();
    EXPECT_EQ( ASTNode::IntegerLiteral, nodes->Type() );
    EXPECT_EQ( "432", nodes->Content() );
  }

  // Test that a single LeftParen is not match as a parameter
  TEST_F( ParserTest, ShouldNotMatchLParenAsParameter ) {
    Add( LeftParen );
    ASTNode *parameter = Parser( tokenStream ).MatchParameter();
    EXPECT_EQ( NULL, parameter );
  }

  // Test that a single RightParen is not matched as a parameter
  TEST_F( ParserTest, ShouldNotMatchRParenAsParameter ) {
    Add( RightParen );
    ASTNode *parameter = Parser( tokenStream ).MatchParameter();
    EXPECT_EQ( NULL, parameter );
  }

  // Test that a single colon is not matched as a parameter
  TEST_F( ParserTest, ShouldNotMatchColonAsParameter ) {
    Add( Colon );
    ASTNode *parameter = Parser( tokenStream ).MatchParameter();
    EXPECT_EQ( NULL, parameter );
  }

  // Function Definition Parsing Tests
  //----------------------------------------------------------------------------

  // Shouldn't match a lone parenthesis as a FunctionDef
  TEST_F( ParserTest, ShouldNotMatchLoneParenAsFunctionDef ) {
    Add( RightParen );
    ASTNode *parameter = Parser( tokenStream ).MatchFunctionDef();
    EXPECT_EQ( NULL, parameter );
  }

  // Should raise an error when a lambda isn't followed by LeftParen
  TEST_F( ParserTest, ShouldRaiseErrorWhenLeftParenDoesntFollowLambda ) {
    Add( Lambda ); Add( RightParen );
    // TODO: Add error checking
  }

  TEST_F( ParserTest, ShouldNotMatchFunctionDefWithNoBlock )  {
    Add( Lambda ); Add( LeftParen ); Add( RightParen );
    Add( EndOfFile );
    ASTNode *functionDef = Parser( tokenStream ).MatchFunctionDef();
    EXPECT_EQ( NULL, functionDef );
  }

  // Should match a Lambda-LParen-RParen-Block as a FunctionDef
  TEST_F( ParserTest, ShouldMatchFunctionDefNoParams ) {
    Add( Lambda ); Add( LeftParen ); Add( RightParen );
    Add( Newline ); Add( IndentIncrease );
    Add( Identifier, "var" ); Add( Equals ); Add( String, "blah" );
    Add( Newline ); Add( IndentDecrease );
    ASTNode *functionDef = Parser( tokenStream ).MatchFunctionDef();
    EXPECT_EQ( ASTNode::FunctionDef, functionDef->Type() );
  }

  // Should match a Lambda-LParen-Param-RParen-Block as a FunctionDef
  TEST_F( ParserTest, ShouldMatchFunctionDef1Param ) {
    Add( Lambda ); Add( LeftParen ); 
    Add( Identifier, "a" ); Add( RightParen );
    Add( Newline ); Add( IndentIncrease );
    Add( Identifier, "var" ); Add( Equals ); Add( String, "blah" );
    Add( Newline ); Add( IndentDecrease );
    ASTNode *functionDef = Parser( tokenStream ).MatchFunctionDef();
    EXPECT_EQ( ASTNode::FunctionDef, functionDef->Type() );

    ASTIterator paramDefs = functionDef->ChildNodes();
    EXPECT_EQ( ASTNode::ParameterDef, paramDefs->Type() );
  }

  // Should Match a FunctionDef with multiple params
  TEST_F( ParserTest, ShouldMatchFunctionDefMultipleParams ) {
    Add( Lambda ); Add( LeftParen ); 
    Add( Identifier, "a" ); Add( Comma );
    Add( Identifier, "b" ); Add( RightParen );
    Add( Newline ); Add( IndentIncrease );
    Add( Identifier, "var" ); Add( Equals ); Add( String, "blah" );
    Add( Newline ); Add( IndentDecrease );
    ASTNode *functionDef = Parser( tokenStream ).MatchFunctionDef();
    EXPECT_EQ( ASTNode::FunctionDef, functionDef->Type() );

    ASTIterator paramDefs = functionDef->ChildNodes();
    EXPECT_EQ( ASTNode::ParameterDef, paramDefs->Type() );
    EXPECT_EQ( ASTNode::ParameterDef, (++paramDefs)->Type() );
  }

  // Block Parsing Tests
  //----------------------------------------------------------------------------
  TEST_F( ParserTest, ShouldNotParseBlockWithoutIndentIncrease ) {
    Add( IndentDecrease );
    ASTNode *block = Parser( tokenStream ).MatchBlock();
    EXPECT_EQ( NULL, block );
  }

  TEST_F( ParserTest, ShouldNotMatchAnEmptyBlock ) {
    Add( IndentIncrease ); Add( IndentDecrease );
    ASTNode *block = Parser( tokenStream ).MatchBlock();
    EXPECT_EQ( NULL, block );
    // TODO: Test that an error is raised here
  }

  TEST_F( ParserTest, ShouldMatchBlockWithAssignment ) {
    Add( IndentIncrease );
    Add( Identifier, "test" ); Add( Equals ); Add( Integer, "123"); Add( Newline );
    Add( IndentDecrease );
    ASTNode *block = Parser( tokenStream ).MatchBlock();
    EXPECT_EQ( ASTNode::Block, block->Type() );

    ASTIterator mutableAssignment = block->ChildNodes();
    EXPECT_EQ( ASTNode::MutableAssignment, mutableAssignment->Type() );
  }

  // MutableAssignment Parsing tests
  //----------------------------------------------------------------------------
  TEST_F( ParserTest, ShouldMatchMutableAssignment ) {
    Add( Identifier, "var" ); Add( Equals ); Add( Integer, "123");
    ASTNode *mutableAssignment = Parser( tokenStream ).MatchMutableAssignment();
    EXPECT_EQ( ASTNode::MutableAssignment, mutableAssignment->Type() );
    EXPECT_EQ( "var", mutableAssignment->Content() );
  }

  // ImmutableAssignment Parsing tests
  TEST_F( ParserTest, ShouldMatchImmutableAssignment ) {
    Add( Identifier, "var" ); Add( Colon ); Add( Integer, "123");
    ASTNode *immutableAssignment = Parser( tokenStream ).MatchImmutableAssignment();
    EXPECT_EQ( ASTNode::ImmutableAssignment, immutableAssignment->Type() );
    EXPECT_EQ( "var", immutableAssignment->Content() );
  }

  // Conditional parsing tests
  //----------------------------------------------------------------------------
  TEST_F( ParserTest, ShouldNotMatchConditionalNotStartingWithIf ) {
    Add( Else );
    ASTNode *conditional = Parser( tokenStream ).MatchConditional();
    EXPECT_EQ( NULL, conditional );
  }

  TEST_F( ParserTest, ShouldMatchConditionalWithOnlyIfClause ) {
    Add( If ); Add( Identifier, "blah" ); Add( Newline );
    Add( IndentIncrease );
    Add( Identifier, "var"); Add( Equals ); Add( Integer, "23" ); Add( Newline );
    Add( IndentDecrease );
    ASTConditionalNode *conditional = Parser( tokenStream ).MatchConditional();
    ASSERT_TRUE( conditional );
    EXPECT_EQ( ASTNode::Conditional, conditional->Type() );
    ASSERT_TRUE( conditional->IfBlock() );
    EXPECT_EQ( ASTNode::Block, conditional->IfBlock()->Type() );
    EXPECT_EQ( NULL, conditional->ElseBlock() );
  }
  
  TEST_F( ParserTest, ShouldMatchConditionWithTwoClauses ) {
    Add( If ); Add( Identifier, "blah" ); Add( Newline );
    Add( IndentIncrease );
    Add( Identifier, "var"); Add( Equals ); Add( Integer, "23" ); Add( Newline );
    Add( IndentDecrease ); Add( Else ); Add( Newline );
    Add( IndentIncrease );
    Add( Identifier, "function" ); Add( LeftParen ); Add( RightParen ); Add(Newline);
    Add( IndentDecrease );
    ASTConditionalNode *conditional = Parser( tokenStream ).MatchConditional();

    ASSERT_TRUE( conditional );
    EXPECT_EQ( ASTNode::Conditional, conditional->Type() );
    ASSERT_TRUE( conditional->IfBlock() );
    EXPECT_EQ( ASTNode::Block, conditional->IfBlock()->Type() );
    ASSERT_TRUE( conditional->ElseBlock() );
    EXPECT_EQ( ASTNode::Block, conditional->ElseBlock()->Type() );
  }

  TEST_F( ParserTest, ShouldNotMatchConditionWithMissingElseBlock ) {
    Add( If ); Add( Identifier, "blah" ); Add( Newline );
    Add( IndentIncrease );
    Add( Identifier, "var"); Add( Equals ); Add( Integer, "23" ); Add( Newline );
    Add( IndentDecrease ); Add( Else ); Add( Newline );
    Add( Identifier, "function" ); Add( LeftParen ); Add( RightParen ); Add(Newline);
    ASTConditionalNode *conditional = Parser( tokenStream ).MatchConditional();

    ASSERT_FALSE( conditional );
  }
  
  // Return statement parsing tests
  //----------------------------------------------------------------------------
  TEST_F( ParserTest, ShouldNotMatchReturnStatementNotStartingWithReturn ) {
    Add( If );
    ASTNode *returnStatement = Parser( tokenStream ).MatchReturnStatement();
    ASSERT_FALSE( returnStatement );
  }

  TEST_F( ParserTest, ShouldMatchReturnStatement ) {
    Add( Return ); 
    Add( Identifier, "a" ); Add( Identifier, "+" ); Add( Identifier, "b" );
    ASTReturnStatementNode *returnStatement = Parser( tokenStream ).MatchReturnStatement();
    ASSERT_TRUE( returnStatement );
    EXPECT_EQ( ASTNode::ReturnStatement, returnStatement->Type() );

    ASSERT_TRUE( returnStatement->ReturnExpr() );
    EXPECT_EQ( ASTNode::FunctionCall, returnStatement->ReturnExpr()->Type() );
  }

  TEST_F( ParserTest, ShouldAddNullLiteralToEmptyReturnStatement ) {
    Add( Return ); Add( Newline );
    ASTReturnStatementNode *returnStatement = Parser( tokenStream ).MatchReturnStatement();
    ASSERT_TRUE( returnStatement );
    EXPECT_EQ( ASTNode::ReturnStatement, returnStatement->Type() );

    ASSERT_TRUE( returnStatement->ReturnExpr() );
    EXPECT_EQ( ASTNode::NullLiteral, returnStatement->ReturnExpr()->Type() );
  }
  
  // Class definition parsing
  //----------------------------------------------------------------------------
  TEST_F( ParserTest, ShouldNotMatchClassDefinitionNotStartingWithClass ) {
    Add( Identifier, "rah" );
    ASTClassDefinitionNode* classDef = Parser( tokenStream ).MatchClassDefinition();
    ASSERT_FALSE( classDef );
  }

  TEST_F( ParserTest, ShouldNotMatchClassDefinitionWithoutANamingIdentifier ) {
    Add( Class ); Add( RightParen );
    ASTClassDefinitionNode* classDef = Parser( tokenStream ).MatchClassDefinition();
    ASSERT_FALSE( classDef );
  }

  TEST_F( ParserTest, ShouldMatchAnEmptyClass ) {
    Add( Class ); Add( Identifier, "Integer" ); Add( Newline );
    ASTClassDefinitionNode* classDef = Parser( tokenStream ).MatchClassDefinition();

    ASSERT_TRUE( classDef );
    EXPECT_EQ( ASTNode::ClassDefinition, classDef->Type() );
    EXPECT_EQ( "Integer", classDef->Content() );
  }

  TEST_F( ParserTest, ShouldMatchClassDefWithAnAssignment) {
    Add( Class ); Add( Identifier, "Integer" ); Add( Newline );
    Add( IndentIncrease );
    Add( Identifier, "rah" ); Add( Colon ); Add( Integer, "123"); Add( Newline );
    Add( IndentDecrease );
    ASTClassDefinitionNode* classDef = Parser( tokenStream ).MatchClassDefinition();

    ASSERT_TRUE( classDef );
    EXPECT_EQ( ASTNode::ClassDefinition, classDef->Type() );
    EXPECT_EQ( "Integer", classDef->Content() );
    
    ASTIterator classBody = classDef->ChildNodes();
    EXPECT_EQ( ASTNode::ImmutableAssignment, classBody->Type() );
  }
  
}
