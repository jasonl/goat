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
#include "goat.h"

// Creates an AST-Node
Node *astCreateNode( enum NODE_TYPE type ) {
  Node *newNode = malloc( sizeof(Node) );
  if (newNode == NULL) {
      goatFatalError("Unable to allocate sufficient memory during parsing.");
  }
  memset(newNode, 0, sizeof(Node));
  newNode->type = type; 
  return newNode;
}

// Recursively frees memory allocated to a node sub-tree
void astFreeNode( Node *node ) {
  Node *childNode = NULL, *tempNode = NULL;

  childNode = node->firstChild;

  while (childNode != NULL) {
    tempNode = childNode->nextSibling;
    astFreeNode( childNode );
    childNode = tempNode;
  }

  free(node);
}

// Append a new AST-Node as the last child to parent,
// setting all child pointers to match.
void astAppendChild( Node *child, Node *parent ) {
  Node *lastSibling = parent->firstChild;

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
void astInsertFirstChild( Node *child, Node *parent ) {
  Node *secondChild;

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

// Helper function to perform look-aheads in the token stream
// where we need to resolve ambiguities.
int astLookaheadFor( Token **curr, enum NODE_TYPE node_type) {
  if((*curr)->next == NULL) return FALSE;

  return ( (*curr)->next->type == node_type );
}
