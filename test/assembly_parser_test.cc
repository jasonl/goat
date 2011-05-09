#include <gtest/gtest.h>
#include "token.hpp"
#include "ast_node.h"
#include "parser.h"

typedef std::list<Token>::iterator TokenIterator;

namespace {
  class AssemblyParserTest : public ::testing::Test {
  protected:
    void Add( TokenType _type, std::string _content = "" ) { 
      tokenStream.push_back( Token( _type, _content ) );
    }
    std::list<Token> tokenStream;
  };

  // IndirectOperandTerm parsing
  //----------------------------------------------------------------------------
  TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandTermWithPlus ) {
    Add( Plus, "+" ); Add( Integer, "4" );
    ASTNode *indirectOpTerm = Parser( tokenStream).MatchIndirectOperandTerm();
    ASSERT_TRUE( indirectOpTerm );
    EXPECT_EQ( ASTNode::IndirectOperandTerm, indirectOpTerm->Type() );
    EXPECT_EQ( "+", indirectOpTerm->Content() );
  }

  TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandTermWithMinus ) {
    Add( Minus, "-" ); Add( Integer, "4" );
    ASTNode *indirectOpTerm = Parser( tokenStream).MatchIndirectOperandTerm();
    ASSERT_TRUE( indirectOpTerm );
    EXPECT_EQ( ASTNode::IndirectOperandTerm, indirectOpTerm->Type() );
    EXPECT_EQ( "-", indirectOpTerm->Content() );
  }

  TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandTermWithMultiply ) {
    Add( Multiply, "*" ); Add( Integer, "4" );
    ASTNode *indirectOpTerm = Parser( tokenStream).MatchIndirectOperandTerm();
    ASSERT_TRUE( indirectOpTerm );
    EXPECT_EQ( ASTNode::IndirectOperandTerm, indirectOpTerm->Type() );
    EXPECT_EQ( "*", indirectOpTerm->Content() );
  }

  TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandTermWithIdentifier ) {
    Add( Plus, "+" ); Add( Identifier, "eax" );
    ASTNode *indirectOpTerm = Parser( tokenStream).MatchIndirectOperandTerm();
    ASSERT_TRUE( indirectOpTerm );
    EXPECT_EQ( ASTNode::IndirectOperandTerm, indirectOpTerm->Type() );
    EXPECT_EQ( "+", indirectOpTerm->Content() );
  }

  // IndirectOperand parsing
  //----------------------------------------------------------------------------

  TEST_F( AssemblyParserTest, ShouldNotMatchIndirectOperandNotStartingLSquare ) {
    Add( RightSquare ); Add( Identifier, "eax" );
    ASTNode *indirectOp = NULL;
    indirectOp = Parser( tokenStream ).MatchIndirectOperand();
    ASSERT_FALSE( indirectOp );
  }

  TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandWithNoTerms ) {
    Add( LeftSquare ); Add( Identifier, "eax" ); Add( RightSquare );
    ASTNode *indirectOp = Parser( tokenStream ).MatchIndirectOperand();
    ASSERT_TRUE( indirectOp );
    EXPECT_EQ( ASTNode::IndirectOperand, indirectOp->Type() );
    EXPECT_EQ( "eax", indirectOp->Content() );
  }

  TEST_F( AssemblyParserTest, ShouldNotMatchIndirectOperandWithoutRSquare ) {
    Add( LeftSquare ); Add( Identifier, "eax" ); Add( Newline );
    ASTNode *indirectOp = NULL;
    indirectOp = Parser( tokenStream ).MatchIndirectOperand();
    ASSERT_FALSE( indirectOp );
  }

  TEST_F( AssemblyParserTest, ShouldMatchIndirectOperandWithTerm ) {
    Add( LeftSquare ); Add( Identifier, "eax" ); 
    Add( Plus, "+"); Add( Integer, "4");
    Add( RightSquare );
    ASTNode *indirectOp = Parser( tokenStream ).MatchIndirectOperand();
    ASSERT_TRUE( indirectOp );
    EXPECT_EQ( ASTNode::IndirectOperand, indirectOp->Type() );
    EXPECT_EQ( "eax", indirectOp->Content() );

    ASTIterator i = indirectOp->ChildNodes();
    EXPECT_EQ( ASTNode::IndirectOperandTerm, i->Type() );
    
  }

  // Operand Parsing
  //----------------------------------------------------------------------------
  
  TEST_F( AssemblyParserTest, ShouldMatchIdentifierAsDirectOperand ) {
    Add( Identifier, "eax");
    ASTNode *operand = Parser( tokenStream ).MatchDirectOperand();
    ASSERT_TRUE( operand );
    EXPECT_EQ( ASTNode::DirectOperand, operand->Type() );
    EXPECT_EQ( "eax", operand->Content() );
  }

  // Instruction Parsing
  //----------------------------------------------------------------------------

  TEST_F( AssemblyParserTest, ShouldMatchInstructionWithoutOperands ) {
    Add( Identifier, "ret" ); Add( Newline );
    ASTNode *instruction = Parser( tokenStream ).MatchInstruction();
    ASSERT_TRUE( instruction );
    EXPECT_EQ( ASTNode::Instruction, instruction->Type() );
    EXPECT_EQ( "ret", instruction->Content() );
  }

  TEST_F( AssemblyParserTest, ShouldMatchInstructionWithImmedOperand ) {
    Add( Identifier, "int" ); Add( Integer, "32" ); Add( Newline );
    ASTNode *instruction = Parser( tokenStream ).MatchInstruction();
    ASSERT_TRUE( instruction );
    EXPECT_EQ( ASTNode::Instruction, instruction->Type() );
    EXPECT_EQ( "int", instruction->Content() );
  }

  TEST_F( AssemblyParserTest, ShouldMatchInstructionWithDirectOperand ) {
    Add( Identifier, "push" ); Add( Identifier, "eax" ); Add( Newline );
    ASTNode *instruction = Parser( tokenStream ).MatchInstruction();
    ASSERT_TRUE( instruction );
    EXPECT_EQ( ASTNode::Instruction, instruction->Type() );
    EXPECT_EQ( "push", instruction->Content() );
    
    ASTIterator operands = instruction->ChildNodes();
    EXPECT_EQ( ASTNode::DirectOperand, operands->Type() );
    EXPECT_EQ( "eax", operands->Content() );
  }

  TEST_F( AssemblyParserTest, ShouldMatchInstructionWithTwoOperands ) {
    Add( Identifier, "mov" ); Add( Identifier, "eax" ); 
    Add( Comma ); Add( Identifier, "ebx" ); Add( Newline );
    ASTNode *instruction = Parser( tokenStream ).MatchInstruction();
    ASSERT_TRUE( instruction );
    EXPECT_EQ( ASTNode::Instruction, instruction->Type() );
    EXPECT_EQ( "mov", instruction->Content() );
    
    ASTIterator operands = instruction->ChildNodes();
    EXPECT_EQ( ASTNode::DirectOperand, operands->Type() );
    EXPECT_EQ( "eax", operands->Content() );

    operands++;
    EXPECT_EQ( ASTNode::DirectOperand, operands->Type() );
    EXPECT_EQ( "ebx", operands->Content() );
  }

  TEST_F( AssemblyParserTest, ShouldMatchInstructionWithLabel ) {
    Add( Label, "not_equal:" ); Add( Identifier, "ret"); Add( Newline );
    ASTNode *instruction = Parser( tokenStream ).MatchInstruction();
    ASSERT_TRUE( instruction );
    EXPECT_EQ( ASTNode::Instruction, instruction->Type() );
    
    ASTIterator operands = instruction->ChildNodes();
    EXPECT_EQ( ASTNode::Label, operands->Type() );
    EXPECT_EQ( "not_equal:", operands->Content() );
  }

  TEST_F( AssemblyParserTest, ShouldMakeDummyInstructionForLabel ) {
    Add( Label, "not_equal:"); Add( Newline );
    ASTNode *instruction = Parser( tokenStream ).MatchInstruction();
    ASSERT_TRUE( instruction );
    EXPECT_EQ( ASTNode::Instruction, instruction->Type() );
    EXPECT_EQ( "", instruction->Content() );
    
    ASTIterator operands = instruction->ChildNodes();
    EXPECT_EQ( ASTNode::Label, operands->Type() );
    EXPECT_EQ( "not_equal:", operands->Content() );
  }
  
  // Assembly Block Parsing
  //----------------------------------------------------------------------------

  TEST_F( AssemblyParserTest, ShouldMatchAssemblyBlock ) {
    Add( Asm ); Add( Newline ); Add( IndentIncrease );
    Add( Identifier, "int" ); Add( Integer, "32" ); Add( Newline );
    Add( IndentDecrease );

    ASTNode *asmBlock = Parser( tokenStream ).MatchInlineAssembly();
    ASSERT_TRUE( asmBlock );
    EXPECT_EQ( ASTNode::InlineAssembly, asmBlock->Type() );
    
    ASTIterator instructions = asmBlock->ChildNodes();
    EXPECT_EQ( ASTNode::Instruction, instructions->Type() );
  }

  TEST_F( AssemblyParserTest, ShouldMatchAssemblyBlockWithBlankLines ) {
    Add( Asm ); Add( Newline ); Add( IndentIncrease );
    Add( Identifier, "int" ); Add( Integer, "32" ); Add( Newline );
    Add( Newline );
    Add( Identifier, "mov" ); Add( Identifier, "eax"); Add( Comma ); Add( Integer, "32"); Add( Newline );
    Add( IndentDecrease ); Add( Newline );

    ASTNode *asmBlock = Parser( tokenStream ).MatchInlineAssembly();
    ASSERT_TRUE( asmBlock );
    EXPECT_EQ( ASTNode::InlineAssembly, asmBlock->Type() );
    
    ASTIterator instructions = asmBlock->ChildNodes();
    EXPECT_EQ( ASTNode::Instruction, instructions->Type() );

    instructions++;
    //EXPECT_EQ( ASTNode::Instruction, instructions->Type() );

  }
  
}
