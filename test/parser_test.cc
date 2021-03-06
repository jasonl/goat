#include <gtest/gtest.h>
#include "goat.h"
#include "token.hpp"
#include "ast_node.h"
#include "build_set.h"
#include "source_file.h"
#include "parser.h"

typedef std::list<Token>::iterator TokenIterator;

#define TYPE(a) (typeid(a).name())

namespace {
  class ParserTest : public ::testing::Test {
  protected:
	  ParserTest() {
		  sourceFile = new ::SourceFile("dummy.gt", false);
		  sourceFile->SetBuildSet(new BuildSet);
	  };

	  ~ParserTest() {
		  delete sourceFile;
	  };

	  void Add( TokenType _type, std::string _content = "" ) {
		  Token token(_type, _content);
		  sourceFile->AddToken(token);
	  }
	  ::SourceFile* sourceFile;
  };

	// Tests correct parsing of an immutable assignement as statement
	TEST_F( ParserTest, ShouldMatchConstantAssignmentAsStatement )
	{
		Add( Identifier, "var"); Add( Colon ); Add( Integer, "123" );
		ASTNode* immutable = Parser( sourceFile ).MatchStatement();
		EXPECT_EQ( typeid(ConstantAssignmentNode).name(), typeid(*immutable).name());
	}

	// Tests correct parsing of a mutable assignment as a statement
	TEST_F( ParserTest, ShouldMatchMutableAssignmentAsStatement )
	{
		Add( Identifier, "var"); Add( Equals ); Add( Integer, "123" );
		ASTNode* _mutable = Parser( sourceFile ).MatchStatement();
		EXPECT_EQ( typeid(MutableAssignmentNode).name(), typeid(*_mutable).name());
	}

	// Tests correct parsing of a function call as a statement
	TEST_F( ParserTest, ShouldMatchFunctionCallAsStatement )
	{
		Add( Identifier, "function_name" );
		Add( LeftParen ); Add( Integer, "1" ); Add( RightParen );
		Add( Newline );
		ASTNode* functionCall = Parser( sourceFile ).MatchStatement();
		EXPECT_EQ( typeid(FunctionCallNode).name(), typeid(*functionCall).name());
	}

	// Tests a string literal is parsed as an expression
	TEST_F( ParserTest, ShouldMatchStringLiteralAsExpression )
	{
		Add( String, "Some String" );
		ASTNode* stringLiteral = Parser( sourceFile ).MatchExpression();
		EXPECT_EQ(typeid(StringLiteralNode).name(), typeid(*stringLiteral).name());
		EXPECT_EQ( "Some String", dynamic_cast<StringLiteralNode*>(stringLiteral)->Contents() );
	}

	// Tests a integer literal is parsed as an expression
	TEST_F( ParserTest, ShouldMatchIntegerLiteralAsExpression )
	{
		Add( Integer, "12345" );
		ASTNode* integerLiteral = Parser( sourceFile ).MatchExpression();
		EXPECT_EQ(TYPE(IntegerLiteralNode), TYPE(*integerLiteral));
		EXPECT_EQ( "12345", dynamic_cast<IntegerLiteralNode*>(integerLiteral)->Contents() );
	}

	TEST_F(ParserTest, ShouldMatchUnsignedIntegerLiteralAsExpression)
	{
		Add(UnsignedInteger, "0x1f00");
		ASTNode* integerLiteral = Parser(sourceFile).MatchExpression();
		EXPECT_EQ(TYPE(UnsignedIntegerLiteralNode), TYPE(*integerLiteral));
		EXPECT_EQ( "0x1f00", dynamic_cast<UnsignedIntegerLiteralNode*>(integerLiteral)->Contents() );
	}

	TEST_F(ParserTest, ShouldMatchTrueLiteralAsExpression)
	{
		Add(True);
		ASTNode* trueLiteral = Parser(sourceFile).MatchExpression();
		EXPECT_EQ(typeid(TrueLiteralNode).name(), typeid(*trueLiteral).name());
	}

	TEST_F(ParserTest, ShouldMatchFalseLiteralAsExpression)
	{
		Add(False);
		ASTNode* falseLiteral = Parser(sourceFile).MatchExpression();
		EXPECT_EQ(TYPE(FalseLiteralNode), TYPE(*falseLiteral));
	}

	TEST_F(ParserTest, ShouldMatchNullLiteralAsExpression)
	{
		Add(Null);
		ASTNode* nullLiteral = Parser(sourceFile).MatchExpression();
		EXPECT_EQ(TYPE(NullLiteralNode), TYPE(*nullLiteral));
	}

	// Tests a variable is parsed as an expression
	TEST_F( ParserTest, ShouldMatchVariableAsExpression )
	{
		Add( Identifier, "var_name" );
		ASTNode* variable = Parser( sourceFile ).MatchExpression();
		EXPECT_EQ(TYPE(VariableNode), TYPE(*variable));
		EXPECT_EQ( "var_name", dynamic_cast<VariableNode*>(variable)->Name() );
	}

	// Tests a class variable is parsed as an expression
	TEST_F(ParserTest, ShouldMatchClassVariableAsExpression)
	{
		Add(ClassVar, "@test");
		ASTNode *expr = Parser(sourceFile).MatchExpression();
		EXPECT_EQ(TYPE(ClassVariableNode), TYPE(*expr));
		EXPECT_EQ("@test", dynamic_cast<ClassVariableNode*>(expr)->Name());
	}

	// Tests a function call is parsed as an expression
	TEST_F( ParserTest, ShouldMatchFunctionCallAsExpression )
	{
		Add( Identifier, "function_name");
		Add( LeftParen ); Add( RightParen );
		ASTNode *functionCall = Parser( sourceFile ).MatchExpression();
		EXPECT_EQ(TYPE(FunctionCallNode), TYPE(*functionCall));
		EXPECT_EQ( "function_name", dynamic_cast<FunctionCallNode*>(functionCall)->Name() );
	}

	TEST_F( ParserTest, ShouldMatchMethodInvocation )
	{
		Add( Identifier, "function_name" );
		Add( LeftParen ); Add( RightParen );
		ASTNode *functionCall = Parser( sourceFile ).MatchMethodInvocation();
		EXPECT_EQ(TYPE(FunctionCallNode), TYPE(*functionCall));
		EXPECT_EQ( "function_name", dynamic_cast<FunctionCallNode*>(functionCall)->Name() );
	}

	// Tests that the parser doesn't match a single identifier without
	// parentheses following as a function call. It's the job of
	// semantic analysis to translate this if required, not the parser.
	TEST_F( ParserTest, ShouldntMatchSingleIdentifierAsFunctionCall )
	{
		Add( Identifier, "function_name" );
		ASTNode *functionCall = Parser( sourceFile ).MatchFunctionCall();
		EXPECT_EQ( NULL, functionCall );
	}

	TEST_F( ParserTest, ShouldntMatchMalformedFunctionCall )
	{
		Add( Identifier, "function_name" );
		Add( RightParen );
		ASTNode *functionCall = Parser( sourceFile ).MatchFunctionCall();
		EXPECT_EQ( NULL, functionCall );
	}

	TEST_F( ParserTest, ShouldMatchAFunctionCallWithParameters )
	{
		Add( Identifier, "function_name"); Add( LeftParen );
		Add( Integer, "1" ); Add( RightParen );
		FunctionCallNode *functionCall = Parser( sourceFile ).MatchFunctionCall();
		EXPECT_EQ(TYPE(FunctionCallNode), TYPE(*functionCall));
		EXPECT_EQ( "function_name", functionCall->Name() );
	}

	TEST_F( ParserTest, ShouldMatchFunctionCallMultipleParams )
	{
		Add( Identifier, "function_name" ); Add( LeftParen );
		Add( Integer, "1" ); Add( Comma );
		Add( String, "abc" ); Add( RightParen );
		FunctionCallNode *functionCall = Parser( sourceFile ).MatchFunctionCall();
		EXPECT_EQ(TYPE(FunctionCallNode), TYPE(*functionCall));
		EXPECT_EQ( "function_name", functionCall->Name() );

		ASTIterator params = functionCall->ChildNodes();
		EXPECT_EQ(TYPE(SelfNode), TYPE(*params));

		params++;
		EXPECT_EQ(TYPE(ParameterNode), TYPE(*params));

		params++;
		EXPECT_EQ(TYPE(ParameterNode), TYPE(*params));
	}

	TEST_F(ParserTest, ShouldMatchFunctionCallWith3Parameters)
	{
		Add(Identifier, "function_name"); Add(LeftParen);
		Add(Integer, "1"); Add(Comma);
		Add(Integer, "2"); Add(Comma);
		Add(String, "abc"); Add(RightParen);

		FunctionCallNode *functionCall = Parser(sourceFile).MatchFunctionCall();
		EXPECT_EQ(TYPE(FunctionCallNode), TYPE(*functionCall));
		EXPECT_EQ("function_name", functionCall->Name());

		ASTIterator params = functionCall->ChildNodes();
		EXPECT_EQ(TYPE(SelfNode), TYPE(*params));

		params++;
		EXPECT_EQ(TYPE(ParameterNode), TYPE(*params));

		params++;
		EXPECT_EQ(TYPE(ParameterNode), TYPE(*params));

		params++;
		EXPECT_EQ(TYPE(ParameterNode), TYPE(*params));
	}

	// Test that a String Literal is matched as a Parameter
	TEST_F( ParserTest, ShouldMatchStringLiteralAsParameter )
	{
		Add( String, "Some String");
		ASTNode *parameter = Parser( sourceFile ).MatchParameter();
		EXPECT_EQ(TYPE(ParameterNode), TYPE(*parameter));

		ASTIterator nodes = parameter->ChildNodes();
		EXPECT_EQ(TYPE(StringLiteralNode), TYPE(*nodes));
		EXPECT_EQ( "Some String", dynamic_cast<StringLiteralNode*>(&(*nodes))->Contents() );
	}

	// Test that a Integer Literal is matched as a Parameter
	TEST_F( ParserTest, ShouldMatchIntegerLiteralAsParameter )
	{
		Add( Integer, "432");
		ASTNode *parameter = Parser( sourceFile ).MatchParameter();
		EXPECT_EQ(TYPE(ParameterNode), TYPE(*parameter));

		ASTIterator nodes = parameter->ChildNodes();
		EXPECT_EQ(TYPE(IntegerLiteralNode), TYPE(*nodes));
		EXPECT_EQ( "432", dynamic_cast<IntegerLiteralNode*>(&(*nodes))->Contents() );
	}

	// Test that a single LeftParen is not match as a parameter
	TEST_F( ParserTest, ShouldNotMatchLParenAsParameter )
	{
		Add( LeftParen );
		ASTNode *parameter = Parser( sourceFile ).MatchParameter();
		EXPECT_EQ( NULL, parameter );
	}

	// Test that a single RightParen is not matched as a parameter
	TEST_F( ParserTest, ShouldNotMatchRParenAsParameter ) {
		Add( RightParen );
		ASTNode *parameter = Parser( sourceFile ).MatchParameter();
		EXPECT_EQ( NULL, parameter );
	}

	// Test that a single colon is not matched as a parameter
	TEST_F( ParserTest, ShouldNotMatchColonAsParameter ) {
		Add( Colon );
		ASTNode *parameter = Parser( sourceFile ).MatchParameter();
		EXPECT_EQ( NULL, parameter );
	}

	// Function Definition Parsing Tests
	//----------------------------------------------------------------------------

	// Shouldn't match a lone parenthesis as a FunctionDef
	TEST_F( ParserTest, ShouldNotMatchLoneParenAsFunctionDef )
	{
		Add( RightParen );
		ASTNode *parameter = Parser( sourceFile ).MatchFunctionDef();
		EXPECT_EQ( NULL, parameter );
	}

	// Should raise an error when a lambda isn't followed by LeftParen
	TEST_F( ParserTest, ShouldRaiseErrorWhenLeftParenDoesntFollowLambda )
	{
		Add( Lambda ); Add( RightParen );
		// TODO: Add error checking
	}

	TEST_F( ParserTest, ShouldNotMatchFunctionDefWithNoBlock )
	{
		Add( Lambda ); Add( LeftParen ); Add( RightParen );
		Add( EndOfFile );
		ASTNode *functionDef = Parser( sourceFile ).MatchFunctionDef();
		EXPECT_EQ( NULL, functionDef );
	}

	// Should match a Lambda-LParen-RParen-Block as a FunctionDef
	TEST_F( ParserTest, ShouldMatchFunctionDefNoParams )
	{
		Add( Lambda ); Add( LeftParen ); Add( RightParen );
		Add( Newline ); Add( IndentIncrease );
		Add( Identifier, "var" ); Add( Equals ); Add( String, "blah" );
		Add( Newline ); Add( IndentDecrease );
		FunctionDefNode *functionDef = Parser( sourceFile ).MatchFunctionDef();
		EXPECT_EQ(TYPE(FunctionDefNode), TYPE(*functionDef));
	}

	// Should match a Lambda-LParen-Param-RParen-Block as a FunctionDef
	TEST_F( ParserTest, ShouldMatchFunctionDef1Param )
	{
		Add( Lambda ); Add( LeftParen );
		Add( Identifier, "a" ); Add( RightParen );
		Add( Newline ); Add( IndentIncrease );
		Add( Identifier, "var" ); Add( Equals ); Add( String, "blah" );
		Add( Newline ); Add( IndentDecrease );
		ASTNode *functionDef = Parser( sourceFile ).MatchFunctionDef();
		EXPECT_EQ(TYPE(FunctionDefNode), TYPE(*functionDef));

		ASTIterator paramDefs = functionDef->ChildNodes();
		EXPECT_EQ(TYPE(ParameterDefNode), TYPE(*paramDefs));
	}

	// Should Match a FunctionDef with multiple params
	TEST_F( ParserTest, ShouldMatchFunctionDefMultipleParams )
	{
		Add( Lambda ); Add( LeftParen );
		Add( Identifier, "a" ); Add( Comma );
		Add( Identifier, "b" ); Add( RightParen );
		Add( Newline ); Add( IndentIncrease );
		Add( Identifier, "var" ); Add( Equals ); Add( String, "blah" );
		Add( Newline ); Add( IndentDecrease );
		ASTNode *functionDef = Parser( sourceFile ).MatchFunctionDef();
		EXPECT_EQ(TYPE(FunctionDefNode), TYPE(*functionDef));

		ASTIterator paramDefs = functionDef->ChildNodes();
		EXPECT_EQ(TYPE(ParameterDefNode), TYPE(*paramDefs));

		paramDefs++;
		EXPECT_EQ(TYPE(ParameterDefNode), TYPE(*paramDefs));
	}

	// Block Parsing Tests
	//----------------------------------------------------------------------------
	TEST_F( ParserTest, ShouldNotParseBlockWithoutIndentIncrease )
	{
		Add( IndentDecrease );
		ASTNode *block = Parser( sourceFile ).MatchBlock();
		EXPECT_EQ( NULL, block );
	}

	TEST_F( ParserTest, ShouldNotMatchAnEmptyBlock )
	{
		Add( IndentIncrease ); Add( IndentDecrease );
		ASTNode *block = Parser( sourceFile ).MatchBlock();
		EXPECT_EQ( NULL, block );
		// TODO: Test that an error is raised here
	}

	TEST_F( ParserTest, ShouldMatchBlockWithAssignment )
	{
		Add( IndentIncrease );
		Add( Identifier, "test" ); Add( Equals ); Add( Integer, "123"); Add( Newline );
		Add( IndentDecrease );
		ASTNode *block = Parser( sourceFile ).MatchBlock();
		EXPECT_EQ(TYPE(BlockNode), TYPE(*block));

		ASTIterator mutableAssignment = block->ChildNodes();
		EXPECT_EQ(TYPE(MutableAssignmentNode), TYPE(*mutableAssignment));
	}

	// MutableAssignment Parsing tests
	//----------------------------------------------------------------------------
	TEST_F( ParserTest, ShouldMatchMutableAssignment )
	{
		Add( Identifier, "var" ); Add( Equals ); Add( Integer, "123");
		MutableAssignmentNode *mutableAssignment = Parser( sourceFile ).MatchMutableAssignment();
		EXPECT_EQ(TYPE(MutableAssignmentNode), TYPE(*mutableAssignment));
		EXPECT_EQ( "var", mutableAssignment->VariableName() );
	}

	// ConstantAssignment Parsing tests
	TEST_F( ParserTest, ShouldMatchConstantAssignment )
	{
		Add( Identifier, "var" ); Add( Colon ); Add( Integer, "123");
		ConstantAssignmentNode *immutableAssignment = Parser( sourceFile ).MatchConstantAssignment();
		EXPECT_EQ(TYPE(ConstantAssignmentNode), TYPE(*immutableAssignment));
		EXPECT_EQ( "var", immutableAssignment->VariableName() );
	}

	// MethodAssignment parsing tests
	//-----------------------------------------------------------------------------

	TEST_F(ParserTest, ShouldMatchMethodAssignment)
	{
		Add(Identifier, "method");
		Add(Colon);
		Add(Lambda);
		Add(LeftParen);
		Add(RightParen);
		Add(Newline);
		Add(IndentIncrease);
		Add(Return);
		Add(Integer, "123");
		Add(Newline);
		Add(IndentDecrease);

		MethodAssignmentNode *methodAssignment = Parser(sourceFile).MatchMethodAssignment();

		EXPECT_EQ(TYPE(MethodAssignmentNode), TYPE(*methodAssignment));
		EXPECT_EQ("method", methodAssignment->Name());
	}

	TEST_F(ParserTest, ShouldMatchClassMethodAssignment)
	{
		Add(Self);
		Add(Period);
		Add(Identifier, "class_method");
		Add(Colon);
		Add(Lambda);
		Add(LeftParen);
		Add(RightParen);
		Add(Newline);
		Add(IndentIncrease);
		Add(Return);
		Add(Integer, "123");
		Add(Newline);
		Add(IndentDecrease);

		ClassMethodAssignmentNode *classMethodAssignment = Parser(sourceFile).MatchClassMethodAssignment();

		EXPECT_EQ(TYPE(ClassMethodAssignmentNode), TYPE(*classMethodAssignment));
		EXPECT_EQ("class_method", classMethodAssignment->Name());
	}

	// Conditional parsing tests
	//----------------------------------------------------------------------------
	TEST_F( ParserTest, ShouldNotMatchConditionalNotStartingWithIf )
	{
		Add( Else );
		ASTNode *conditional = Parser( sourceFile ).MatchConditional();
		EXPECT_EQ( NULL, conditional );
	}

	TEST_F( ParserTest, ShouldMatchConditionalWithOnlyIfClause )
	{
		Add( If ); Add( Identifier, "blah" ); Add( Newline );
		Add( IndentIncrease );
		Add( Identifier, "var"); Add( Equals ); Add( Integer, "23" ); Add( Newline );
		Add( IndentDecrease );
		ConditionalNode *conditional = Parser( sourceFile ).MatchConditional();
		ASSERT_TRUE( conditional );
		EXPECT_EQ(TYPE(ConditionalNode), TYPE(*conditional));

		ASSERT_TRUE( conditional->IfBlock() );
		EXPECT_EQ(TYPE(BlockNode), TYPE(*(conditional->IfBlock())));
		EXPECT_EQ( NULL, conditional->ElseBlock() );
	}

	TEST_F( ParserTest, ShouldMatchConditionWithTwoClauses )
	{
		Add( If ); Add( Identifier, "blah" ); Add( Newline );
		Add( IndentIncrease );
		Add( Identifier, "var"); Add( Equals ); Add( Integer, "23" ); Add( Newline );
		Add( IndentDecrease ); Add( Else ); Add( Newline );
		Add( IndentIncrease );
		Add( Identifier, "function" ); Add( LeftParen ); Add( RightParen ); Add(Newline);
		Add( IndentDecrease );
		ConditionalNode *conditional = Parser( sourceFile ).MatchConditional();

		ASSERT_TRUE( conditional );
		EXPECT_EQ(TYPE(ConditionalNode), TYPE(*conditional));

		ASSERT_TRUE( conditional->IfBlock() );
		EXPECT_EQ(TYPE(BlockNode), TYPE(*(conditional->IfBlock())));

		ASSERT_TRUE( conditional->ElseBlock() );
		EXPECT_EQ(TYPE(BlockNode), TYPE(*(conditional->ElseBlock())));
	}

	TEST_F( ParserTest, ShouldNotMatchConditionWithMissingElseBlock )
	{
		Add( If ); Add( Identifier, "blah" ); Add( Newline );
		Add( IndentIncrease );
		Add( Identifier, "var"); Add( Equals ); Add( Integer, "23" ); Add( Newline );
		Add( IndentDecrease ); Add( Else ); Add( Newline );
		Add( Identifier, "function" ); Add( LeftParen ); Add( RightParen ); Add(Newline);
		ConditionalNode *conditional = Parser( sourceFile ).MatchConditional();

		ASSERT_FALSE( conditional );
	}

	// Return statement parsing tests
	//----------------------------------------------------------------------------
	TEST_F( ParserTest, ShouldNotMatchReturnStatementNotStartingWithReturn )
	{
		Add( If );
		ASTNode *returnStatement = Parser( sourceFile ).MatchReturnStatement();
		ASSERT_FALSE( returnStatement );
	}

	TEST_F( ParserTest, ShouldMatchReturnStatement )
	{
		Add( Return );
		Add( Identifier, "a" ); Add( Identifier, "+" ); Add( Identifier, "b" );
		ReturnStatementNode *returnStatement = Parser( sourceFile ).MatchReturnStatement();
		ASSERT_TRUE( returnStatement );
		EXPECT_EQ(TYPE(ReturnStatementNode), TYPE(*returnStatement));

		ASSERT_TRUE( returnStatement->ReturnExpr() );
		EXPECT_EQ(TYPE(FunctionCallNode), TYPE(*(returnStatement->ReturnExpr())));
	}

	TEST_F( ParserTest, ShouldAddNullLiteralToEmptyReturnStatement )
	{
		Add( Return ); Add( Newline );
		ReturnStatementNode *returnStatement = Parser( sourceFile ).MatchReturnStatement();
		ASSERT_TRUE( returnStatement );
		EXPECT_EQ(TYPE(ReturnStatementNode), TYPE(*returnStatement));

		ASSERT_TRUE( returnStatement->ReturnExpr() );
		EXPECT_EQ(TYPE(NullLiteralNode), TYPE(*(returnStatement->ReturnExpr())));
	}

	// Class definition parsing
	//----------------------------------------------------------------------------
	TEST_F( ParserTest, ShouldNotMatchClassDefinitionNotStartingWithClass )
	{
		Add( Identifier, "rah" );
		ClassDefinitionNode* classDef = Parser( sourceFile ).MatchClassDefinition();
		ASSERT_FALSE( classDef );
	}

	TEST_F( ParserTest, ShouldNotMatchClassDefinitionWithoutANamingIdentifier )
	{
		Add( Class ); Add( RightParen );
		ClassDefinitionNode* classDef = Parser( sourceFile ).MatchClassDefinition();
		ASSERT_FALSE( classDef );
	}

	TEST_F( ParserTest, ShouldMatchAnEmptyClass )
	{
		Add( Class ); Add( Identifier, "Integer" ); Add( Newline );
		ClassDefinitionNode* classDef = Parser( sourceFile ).MatchClassDefinition();

		ASSERT_TRUE( classDef );
		EXPECT_EQ(TYPE(ClassDefinitionNode), TYPE(*classDef));
		EXPECT_EQ( "Integer", classDef->Name() );
	}

	TEST_F( ParserTest, ShouldMatchClassDefWithAnAssignment)
	{
		Add( Class ); Add( Identifier, "Integer" ); Add( Newline );
		Add( IndentIncrease );
		Add( Identifier, "rah" ); Add( Colon ); Add( Integer, "123"); Add( Newline );
		Add( IndentDecrease );
		ClassDefinitionNode* classDef = Parser( sourceFile ).MatchClassDefinition();

		ASSERT_TRUE( classDef );
		EXPECT_EQ(TYPE(ClassDefinitionNode), TYPE(*classDef));
		EXPECT_EQ( "Integer", classDef->Name() );

		ASTIterator classBody = classDef->ChildNodes();
		EXPECT_EQ(TYPE(MethodAssignmentNode), TYPE(*classBody));
	}

	// Singleton Definition Parsing
	//-----------------------------------------------------------------------------

	TEST_F(ParserTest, ShouldNotMatchSingletonDefinitionNotStartingWithSingleton)
	{
		Add(Identifier, "rah");
		SingletonDefinitionNode* sd = Parser(sourceFile).MatchSingletonDefinition();

		EXPECT_FALSE(sd);
	}

	TEST_F(ParserTest, ShouldNotMatchSingletonDefinitionWithoutIdentifier)
	{
		Add(Singleton); Add(RightParen);
		SingletonDefinitionNode* sd = Parser(sourceFile).MatchSingletonDefinition();

		EXPECT_FALSE(sd);
	}

	TEST_F(ParserTest, ShouldMatchEmptySingletonDefinition)
	{
		Add(Singleton); Add(Identifier, "Test"), Add(Newline);
		SingletonDefinitionNode* sd = Parser(sourceFile).MatchSingletonDefinition();

		ASSERT_TRUE(sd);
		EXPECT_EQ(TYPE(SingletonDefinitionNode), TYPE(*sd));
		EXPECT_EQ("Test", sd->Name());
	}

	TEST_F(ParserTest, ShouldMatchSingletonDefinitionWithMethodAssignment)
	{
		Add(Singleton); Add(Identifier, "Test"); Add(Newline);
		Add(IndentIncrease); Add(Identifier, "method"); Add(Colon);
		Add(Lambda); Add(LeftParen); Add(RightParen); Add(Newline);
		Add(IndentIncrease); Add(Return); Add(Null); Add(Newline);
		Add(IndentDecrease);
		Add(IndentDecrease);

		SingletonDefinitionNode* sd = Parser(sourceFile).MatchSingletonDefinition();

		ASSERT_TRUE(sd);
		EXPECT_EQ(TYPE(SingletonDefinitionNode), TYPE(*sd));
		EXPECT_EQ("Test", sd->Name());
	}
}
