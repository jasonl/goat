/*
 * File:   lexer.h
 * Author: Jason Langenauer <jason@jasonlangenauer.com>
 *
 * Created on 12 November 2009, 6:18 PM
 */

#ifndef __LEXER_H
#define	__LEXER_H

#include "token.hpp"

// Forward declarations
class SourceFile;

// 32-bit wide integer to hold the code-point value
typedef unsigned long w_char;

// This struct holds the UTF-8 and Unicode representation
typedef struct {
    w_char wchar;            // The unencoded value
    int bytes;               // Number of bytes in the code point.
    char utf8[4];            // UTF-8 encoded value
} CodePoint;

class Lexer {
 public:
  Lexer( char*, char*, SourceFile* );
  virtual void Lex();
 protected:
  int currentLine, prevIndent, indent;
  TokenType lexerState;
  char *thunkStart, *thunkEnd;
  char *sourceCurr, *sourceNext, *sourceEnd;
  SourceFile *sourceFile;
  void StartThunk( CodePoint& );
  void StartThunkAtNext( CodePoint& );
  void PushIndentToken();
  TokenType PushToken();
  void PushEmptyToken();
  void GetNextCodePoint( CodePoint* );
  void TranslateKeywordToken( Token& );
  void DefaultStateTransitions( CodePoint& );
};

#endif	/* _LEXER_H */

