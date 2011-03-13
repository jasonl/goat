/* 
 * File:   goat.h
 * Author: jason
 *
 * Created on 14 November 2009, 10:41 PM
 */

#ifndef _GOAT_H
#define	_GOAT_H

#include <string>

#define TRUE 1
#define FALSE 0

class ASTNode;

#define VERBOSE_TOKENS 0x01
#define VERBOSE_AST 0x02
#define VERBOSE_SCOPES 0x04
#define VERBOSE_ASM 0x08

std::string parseCommandLine( int, char**, int*, bool*);
void goatFatalError( std::string );
void goatError( int, std::string, ... );
#endif	/* _GOAT_H */

