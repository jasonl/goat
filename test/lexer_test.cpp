#include <gtest/gtest.h>
#include "lexer.h"
#include "source_file.h"

typedef std::list<Token>::iterator TokenIterator;

namespace {

  class LexerTest : public ::testing::Test {
  protected:
    LexerTest() {
      sf = NULL;
    }

    ~LexerTest() {
      if(sf != NULL ) delete sf;
    }

    TokenIterator LoadAndTokenize( std::string _name ) {
      sf = new SourceFile( _name, true );
      sf->Tokenize();
      return sf->GetTokenStream().begin();
    }

    SourceFile *sf;
    Lexer *lex;
  };

  // Tests tokenisation of a standard function definition
  //
  // Contents of test/function_test.gt:
  // test: λ( test_param )

  TEST_F( LexerTest, ShouldTokenizeFunction ) {
    TokenIterator i = LoadAndTokenize( "fixtures/function_test.gt" );

    EXPECT_EQ( Identifier, i->Type() );
    EXPECT_EQ( "test", i->Content() );
    EXPECT_EQ( Equals, (++i)->Type() );
    EXPECT_EQ( Lambda, (++i)->Type() );
    EXPECT_EQ( LeftParen, (++i)->Type() );
    EXPECT_EQ( Identifier, (++i)->Type() );
    EXPECT_EQ( "test_param", i->Content() );
    EXPECT_EQ( RightParen, (++i)->Type() );
    EXPECT_EQ( Newline, (++i)->Type() );
    EXPECT_EQ( EndOfFile, (++i)->Type() );
  }

  // Tests tokenization of a variety of tokens, not necessarily
  // in an order that is syntactically correct.
  //
  // Contents of test/token_test.gt:
  // ():=; Comment
  // identifier.
  //   another_identifier
  //   123 "A String",
  // "And Another String"

  TEST_F( LexerTest, ShouldTokenizeTokens ) {
    TokenIterator i = LoadAndTokenize( "fixtures/token_test.gt" );

    EXPECT_EQ( LeftParen, i->Type() );
    EXPECT_EQ( RightParen, (++i)->Type() );
    EXPECT_EQ( Colon, (++i)->Type() );
    EXPECT_EQ( Equals, (++i)->Type() );
    EXPECT_EQ( Newline, (++i)->Type() );
    EXPECT_EQ( Identifier, (++i)->Type() );
    EXPECT_EQ( "identifier", i->Content() );
    EXPECT_EQ( Period, (++i)->Type() );
    EXPECT_EQ( Newline, (++i)->Type() );
    EXPECT_EQ( IndentIncrease, (++i)->Type() );
    EXPECT_EQ( Identifier, (++i)->Type() );
    EXPECT_EQ( "another_identifier", i->Content() );
    EXPECT_EQ( Newline, (++i)->Type() );
    EXPECT_EQ( Integer, (++i)->Type() );
    EXPECT_EQ( "123", i->Content() );
    EXPECT_EQ( String, (++i)->Type() );
    EXPECT_EQ( "A String", i->Content() );
    EXPECT_EQ( Comma, (++i)->Type() );
    EXPECT_EQ( Newline, (++i)->Type() );
    EXPECT_EQ( IndentDecrease, (++i)->Type() );
    EXPECT_EQ( String, (++i)->Type() );
    EXPECT_EQ( "And Another String", i->Content() );
    EXPECT_EQ( EndOfFile, (++i)->Type() );
  }

  // Tests correct conversion of identifier tokens for language
  // Keywords into the appropriate keyword tokens
  //
  // Contents of test/keywords.gt
  // if else class return
  TEST_F( LexerTest, ShouldTokenizeKeywords ) {
    TokenIterator i = LoadAndTokenize( "fixtures/keywords.gt" );

    EXPECT_EQ( If, i->Type() );
    EXPECT_EQ( Else, (++i)->Type() );
    EXPECT_EQ( Class, (++i)->Type() );
    EXPECT_EQ( Return, (++i)->Type() );
  }

  // Tests correct tokenization of inline assembly
  TEST_F( LexerTest, ShouldTokenizeAssembly ) {
    TokenIterator i = LoadAndTokenize( "fixtures/asm.gt" );

    EXPECT_EQ( Asm, i->Type() );
    EXPECT_EQ( Newline, (++i)->Type() );
    EXPECT_EQ( IndentIncrease, (++i)->Type() );
    EXPECT_EQ( Label, (++i)->Type() );
    EXPECT_EQ( "label", i->Content() );
    EXPECT_EQ( Identifier, (++i)->Type() );
    EXPECT_EQ( "mov", i->Content() );
    EXPECT_EQ( Identifier, (++i)->Type() );
    EXPECT_EQ( "eax", i->Content() );
    EXPECT_EQ( Comma, (++i)->Type() );
    EXPECT_EQ( Integer, (++i)->Type() );
    EXPECT_EQ( "32", i->Content() );
    EXPECT_EQ( Newline, (++i)->Type() );
    EXPECT_EQ( Identifier, (++i)->Type());
    EXPECT_EQ( "mov", i->Content());
    EXPECT_EQ( AddressString, (++i)->Type());
    EXPECT_EQ( "Integer", i->Content());
    EXPECT_EQ( Comma, (++i)->Type() );
    EXPECT_EQ( HashString, (++i)->Type());
    EXPECT_EQ( "Integer", i->Content());
  }


}
