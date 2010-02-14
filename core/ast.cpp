/*
 * ast.c
 *
 * Helper functions for managing the Abstract Syntax Tree of a Goat Program
 *
 */

#include <malloc.h>
#include <string.h>
#include "lexer.h"
#include "ast.h"
#include "ast_node.h"
#include "goat.h"

// Insert a new AST-Node as the first child, rather than
// the last one.
void astInsertFirstChild( ASTNode *child, ASTNode *parent ) {
  ASTNode *secondChild;

  child->parent = parent;

  if( !(int)parent->firstChild) {
    parent->firstChild = child;
    return;
  }

  secondChild = parent->firstChild;
  parent->firstChild = child;
  secondChild->prevSibling = child;
  child->nextSibling = secondChild;
  return;
}


