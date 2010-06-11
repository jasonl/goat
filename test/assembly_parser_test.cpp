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

}
