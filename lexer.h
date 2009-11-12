/* 
 * File:   lexer.h
 * Author: jason
 *
 * Created on 12 November 2009, 6:18 PM
 */

#ifndef _LEXER_H
#define	_LEXER_H

// 32-bit wide integer to hold the code-point value
typedef unsigned long w_char;

// This struct holds the current character being read
typedef struct {
    w_char wchar;            // The unencoded value
    char utf8[4];            // UTF-8 encoded value
} CodePoint;

// Function prototypes
int goatLexer( char* );
size_t goatGetFileSize( int );
char *goatMapFileToMemory( int, size_t );
void goatGetNextCodePoint( CodePoint*, char**, char**);

#endif	/* _LEXER_H */

