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

// Recursively frees memory allocated to a node sub-tree
void astFreeNode( ASTNode *node ) {
  ASTNode *childNode = NULL, *tempNode = NULL;

  childNode = node->firstChild;

  while (childNode != NULL) {
    tempNode = childNode->nextSibling;
    astFreeNode( childNode );
    childNode = tempNode;
  }

  delete node;
}

// Append a new AST-Node as the last child to parent,
// setting all child pointers to match.
void astAppendChild( ASTNode *child, ASTNode *parent ) {
  ASTNode *lastSibling = parent->firstChild;

  child->parent = parent;

  if( !(int)parent->firstChild ) {
    parent->firstChild = child;
    return;
  }

  // Find the last child node
  while( (int)lastSibling ) {
    if( (int)lastSibling->nextSibling ) {
      lastSibling = lastSibling->nextSibling;
    } else {
      break;
    }
  }

  lastSibling->nextSibling = child;
  child->prevSibling = lastSibling;
  return;
}

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


