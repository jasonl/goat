#include <gtest/gtest.h>
#include "goat.h"
#include "token.hpp"
#include "ast_node.h"
#include "source_file.h"
#include "parser.h"

typedef std::list<Token>::iterator TokenIterator;

#define TYPE(a) (typeid(a).name())

namespace {
  class AssemblyParserTest : public ::testing::Test {
  protected:
	  AssemblyParserTest() {
		  sourceFile = new ::SourceFile("dummy.txt", false);
	  };

	  ~AssemblyParserTest() {
		  delete sourceFile;
	  };

    void Add( TokenType _type, std::string _content = "" ) {
		Token token( _type, _content );
	   sourceFile->AddToken(token);
    }
	  ::SourceFile *sourceFile;
  };

	// IndirectOperandTerm parsing
	//----------------------------------------------------------------------------
	TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandTermWithPlus )
	{
		Add( Plus, "+" ); Add( Integer, "4" );
		IndirectOperandTermNode *indirectOpTerm = Parser( sourceFile).MatchIndirectOperandTerm();
		ASSERT_TRUE( indirectOpTerm );
		EXPECT_EQ( TYPE(IndirectOperandTermNode), TYPE(*indirectOpTerm));
		EXPECT_EQ( "+", indirectOpTerm->Operation() );
	}

	TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandTermWithMinus )
	{
		Add( Minus, "-" ); Add( Integer, "4" );
		IndirectOperandTermNode *indirectOpTerm = Parser( sourceFile).MatchIndirectOperandTerm();
		ASSERT_TRUE( indirectOpTerm );
		EXPECT_EQ(TYPE(IndirectOperandTermNode), TYPE(*indirectOpTerm));
		EXPECT_EQ( "-", indirectOpTerm->Operation() );
	}

	TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandTermWithMultiply )
	{
		Add( Multiply, "*" ); Add( Integer, "4" );
		IndirectOperandTermNode *indirectOpTerm = Parser( sourceFile).MatchIndirectOperandTerm();
		ASSERT_TRUE( indirectOpTerm );
		EXPECT_EQ(TYPE(IndirectOperandTermNode), TYPE(*indirectOpTerm));
		EXPECT_EQ( "*", indirectOpTerm->Operation() );
	}

	TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandTermWithIdentifier )
	{
		Add( Plus, "+" ); Add( Identifier, "eax" );
		IndirectOperandTermNode *indirectOpTerm = Parser( sourceFile).MatchIndirectOperandTerm();
		ASSERT_TRUE( indirectOpTerm );
		EXPECT_EQ(TYPE(IndirectOperandTermNode), TYPE(*indirectOpTerm));
		EXPECT_EQ( "+", indirectOpTerm->Operation() );
	}

	// IndirectOperand parsing
	//----------------------------------------------------------------------------

	TEST_F( AssemblyParserTest, ShouldNotMatchIndirectOperandNotStartingLSquare )
	{
		Add( RightSquare ); Add( Identifier, "eax" );
		ASTNode *indirectOp = NULL;
		indirectOp = Parser( sourceFile ).MatchIndirectOperand();
		ASSERT_FALSE( indirectOp );
	}

	TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandWithNoTerms )
	{
		Add( LeftSquare ); Add( Identifier, "eax" ); Add( RightSquare );
		IndirectOperandNode *indirectOp = Parser( sourceFile ).MatchIndirectOperand();
		ASSERT_TRUE( indirectOp );
		EXPECT_EQ(TYPE(IndirectOperandNode), TYPE(*indirectOp));
		EXPECT_EQ( "eax", indirectOp->Register() );
	}

	TEST_F( AssemblyParserTest, ShouldNotMatchIndirectOperandWithoutRSquare )
	{
		Add( LeftSquare ); Add( Identifier, "eax" ); Add( Newline );
		ASTNode *indirectOp = NULL;
		indirectOp = Parser( sourceFile ).MatchIndirectOperand();
		ASSERT_FALSE( indirectOp );
	}

	TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandWithTerm )
	{
		Add( LeftSquare ); Add( Identifier, "eax" );
		Add( Plus, "+"); Add( Integer, "4");
		Add( RightSquare );
		IndirectOperandNode *indirectOp = Parser( sourceFile ).MatchIndirectOperand();
		ASSERT_TRUE( indirectOp );
		EXPECT_EQ(TYPE(IndirectOperandNode), TYPE(*indirectOp));
		EXPECT_EQ( "eax", indirectOp->Register() );

		ASTIterator i = indirectOp->ChildNodes();
		EXPECT_EQ(TYPE(IndirectOperandTermNode), TYPE(*i));
	}

	// Operand Parsing
	//----------------------------------------------------------------------------

	TEST_F( AssemblyParserTest, ShouldMatchIdentifierAsDirectOperand )
	{
		Add( Identifier, "eax");
		DirectOperandNode *operand = Parser( sourceFile ).MatchDirectOperand();
		ASSERT_TRUE( operand );
		EXPECT_EQ(TYPE(DirectOperandNode), TYPE(*operand));
		EXPECT_EQ( "eax", operand->Register() );
	}

	// Instruction Parsing
	//----------------------------------------------------------------------------

	TEST_F( AssemblyParserTest, ShouldMatchInstructionWithoutOperands )
	{
		Add( Identifier, "ret" ); Add( Newline );
		InstructionNode *instruction = Parser( sourceFile ).MatchInstruction();
		ASSERT_TRUE( instruction );
		EXPECT_EQ(TYPE(InstructionNode), TYPE(*instruction));
		EXPECT_EQ( "ret", instruction->Mnemonic() );
	}

	TEST_F( AssemblyParserTest, ShouldMatchInstructionWithImmedOperand )
	{
		Add( Identifier, "int" ); Add( Integer, "32" ); Add( Newline );
		InstructionNode *instruction = Parser( sourceFile ).MatchInstruction();
		ASSERT_TRUE( instruction );
		EXPECT_EQ(TYPE(InstructionNode), TYPE(*instruction));
		EXPECT_EQ( "int", instruction->Mnemonic() );
	}

	TEST_F(AssemblyParserTest, ShouldMatchInstructionWithModifiedOperand)
	{
		Add(Identifier, "push"); Add(Identifier, "dword"); Add(Integer, "0"); Add(Newline);
		InstructionNode *instruction = Parser(sourceFile).MatchInstruction();
		ASSERT_TRUE(instruction);
		EXPECT_EQ(TYPE(InstructionNode), TYPE(*instruction));
		EXPECT_EQ("push", instruction->Mnemonic());

		ASTIterator operands = instruction->ChildNodes();
		EXPECT_EQ(TYPE(ImmediateOperandNode), TYPE(*operands));
		EXPECT_EQ("0", dynamic_cast<ImmediateOperandNode*>(&(*operands))->Content());
	}

	TEST_F( AssemblyParserTest, ShouldMatchInstructionWithDirectOperand )
	{
		Add( Identifier, "push" ); Add( Identifier, "eax" ); Add( Newline );
		InstructionNode *instruction = Parser( sourceFile ).MatchInstruction();
		ASSERT_TRUE( instruction );
		EXPECT_EQ(TYPE(InstructionNode), TYPE(*instruction));
		EXPECT_EQ( "push", instruction->Mnemonic() );

		ASTIterator operands = instruction->ChildNodes();
		EXPECT_EQ(TYPE(DirectOperandNode), TYPE(*operands));
		EXPECT_EQ( "eax", dynamic_cast<DirectOperandNode*>(&(*operands))->Register() );
	}

	TEST_F( AssemblyParserTest, ShouldMatchInstructionWithTwoOperands )
	{
		Add( Identifier, "mov" ); Add( Identifier, "eax" );
		Add( Comma ); Add( Identifier, "ebx" ); Add( Newline );
		InstructionNode *instruction = Parser( sourceFile ).MatchInstruction();
		ASSERT_TRUE( instruction );
		EXPECT_EQ(TYPE(InstructionNode), TYPE(*instruction));
		EXPECT_EQ( "mov", instruction->Mnemonic() );

		ASTIterator operands = instruction->ChildNodes();
		EXPECT_EQ(TYPE(DirectOperandNode), TYPE(*operands));
		EXPECT_EQ( "eax", dynamic_cast<DirectOperandNode*>(&(*operands))->Register() );

		operands++;
		EXPECT_EQ(TYPE(DirectOperandNode), TYPE(*operands));
		EXPECT_EQ( "ebx", dynamic_cast<DirectOperandNode*>(&(*operands))->Register() );
	}

	TEST_F( AssemblyParserTest, ShouldMatchInstructionWithLabel )
	{
		Add( Label, "not_equal:" ); Add( Identifier, "ret"); Add( Newline );
		InstructionNode *instruction = Parser( sourceFile ).MatchInstruction();
		ASSERT_TRUE( instruction );
		EXPECT_EQ(TYPE(InstructionNode), TYPE(*instruction));
		EXPECT_EQ( "not_equal:", instruction->Label() );
	}

	TEST_F( AssemblyParserTest, ShouldMakeDummyInstructionForLabel )
	{
		Add( Label, "not_equal:"); Add( Newline );
		InstructionNode *instruction = Parser( sourceFile ).MatchInstruction();
		ASSERT_TRUE( instruction );
		EXPECT_EQ(TYPE(InstructionNode), TYPE(*instruction));
		EXPECT_EQ( "", instruction->Mnemonic() );
		EXPECT_EQ( "not_equal:", instruction->Label() );
	}

	// Assembly Block Parsing
	//----------------------------------------------------------------------------

	TEST_F( AssemblyParserTest, ShouldMatchAssemblyBlock )
	{
		Add( Asm ); Add( Newline ); Add( IndentIncrease );
		Add( Identifier, "int" ); Add( Integer, "32" ); Add( Newline );
		Add( IndentDecrease );

		ASTNode *asmBlock = Parser( sourceFile ).MatchInlineAssembly();
		ASSERT_TRUE( asmBlock );
		EXPECT_EQ(TYPE(InlineAssemblyNode), TYPE(*asmBlock));

		ASTIterator instructions = asmBlock->ChildNodes();
		EXPECT_EQ(TYPE(InstructionNode), TYPE(*instructions));
	}

	TEST_F( AssemblyParserTest, ShouldMatchAssemblyBlockWithBlankLines )
	{
		Add( Asm ); Add( Newline ); Add( IndentIncrease );
		Add( Identifier, "int" ); Add( Integer, "32" ); Add( Newline );
		Add( Newline );
		Add( Identifier, "mov" ); Add( Identifier, "eax"); Add( Comma ); Add( Integer, "32"); Add( Newline );
		Add( IndentDecrease ); Add( Newline );

		ASTNode *asmBlock = Parser( sourceFile ).MatchInlineAssembly();
		ASSERT_TRUE( asmBlock );
		EXPECT_EQ(TYPE(InlineAssemblyNode), TYPE(*asmBlock));

		ASTIterator instructions = asmBlock->ChildNodes();
		EXPECT_EQ(TYPE(InstructionNode), TYPE(*instructions));

		instructions++;
		EXPECT_EQ(TYPE(InstructionNode), TYPE(*instructions));
  }

}
