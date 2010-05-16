#include <gtest/gtest.h>

namespace {
  class ParserTest : public ::testing::Test {
  protected:
    void Empty() { tokenStream.empty() };
    void Add( TokenType _type, std::string _content = "" ) { 
      tokenStream.push_back( Token( _type, _content ) );
    }
    std::list<Token> tokenStream;
  };

  // Tests correct 

}
