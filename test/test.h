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
#endif
