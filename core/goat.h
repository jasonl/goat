/* 
 * File:   goat.h
 * Author: jason
 *
 * Created on 14 November 2009, 10:41 PM
 */

#ifndef _GOAT_H
#define	_GOAT_H

// Token types
enum TOKEN_TYPE { Whitespace,
                  Indent,
                  Comment,
                  Newline,
                  Identifier,
                  RightParen,
                  LeftParen,
                  Lambda,
                  Colon,
                  Period,
                  Comma,
                  Equals,
                  End,
                  Integer,
                  String,
                  If,
                  Else,
                  HashRocket,
                  IndentIncrease,
                  IndentDecrease
                  };

typedef struct _Token {
    enum TOKEN_TYPE type;
    int line_no;
    char *content;
    struct _Token *next;
} Token;

typedef struct _GoatState {
    Token *tokens;          // Head node of the linked list of lexical tokens
} GoatState;

void goatPrintTokens( GoatState* );

#endif	/* _GOAT_H */

