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

struct _Token;
class ASTNode;

typedef struct _GoatState {
  struct _Token *tokens;          // Head node of the linked list of lexical tokens
  ASTNode *astRoot;          // Root node of the AST tree
  int verbose;                    // Print more information than usual
  char *sourceFile;               // Input filename
} GoatState;

void goatPrintTokens( GoatState* );
void goatParseArguments( GoatState*, int, char**);
void goatFatalError( std::string );
void goatError( int, std::string, ... );
#endif	/* _GOAT_H */

