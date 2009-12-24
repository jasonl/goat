#ifndef __TEST_H
#define __TEST_H

void assert( int, char* );

void LexerTest();
void testTokenLexing();
void testFunctionLexing();

void ParserTest();
void testExpressionParsing();
void testFunctionCallParsing();
void testFunctionParameterParsing();
void testFunctionDefinitionParsing();
void testBlockParsing();
void testMutableAssignmentParsing();
void testImmutableAssignmentParsing();

extern int error_count;
extern int assert_count;
extern int failure_count;

#define ASSERT_ERROR( function ) \
  int curr_error_count = error_count; \
  ( function ); \
  assert((error_count > curr_error_count), "An error was expected; none was generated");
#endif
