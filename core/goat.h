/* 
 * File:   goat.h
 * Author: jason
 *
 * Created on 14 November 2009, 10:41 PM
 */

#ifndef _GOAT_H
#define	_GOAT_H

struct _Token;
struct _Node;

typedef struct _GoatState {
  struct _Token *tokens;          // Head node of the linked list of lexical tokens
  struct _Node *astRoot;          // Root node of the AST tree
  int verbose;                    // Print more information than usual
  char *sourceFile;               // Input filename
} GoatState;

void goatPrintTokens( GoatState* );
void goatParseArguments( GoatState*, int, char**);
void goatFatalError( char* );
#endif	/* _GOAT_H */

