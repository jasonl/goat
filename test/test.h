#ifndef __TEST_H
#define __TEST_H
#include <string>

void assert( int, std::string );

void LexerTest();
void testTokenLexing();
void testFunctionLexing();
void testKeywordLexing();

class ParserTest {
  friend void goatError(int, std::string, ...);
 public:
  ParserTest();
  static int error_count;
 private:
  static void testExpressionParsing();
  static void testFunctionCallParsing();
  static void testMethodInvocationParsing();
  static void testFunctionParameterParsing();
  static void testFunctionDefinitionParsing();
  static void testBlockParsing();
  static void testStatementParsing();
  static void testMutableAssignmentParsing();
  static void testImmutableAssignmentParsing();
  static void testConditionalParsing();
  static void testReturnParsing();
  static void testClassDefinitionParsing();
  static Token* createToken( Token*, enum TOKEN_TYPE, std::string );
};

#define ASSERT_ERROR( function ) \
  int curr_error_count = ParserTest::error_count;	\
  ( function ); \
  assert((ParserTest::error_count > curr_error_count), "An error was expected; none was generated");
#endif
