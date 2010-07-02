#include <string>
#include <iostream>
#include "token.hpp"
#include "lexer.h"
#include "ast_node.h"

ASTNode::ASTNode( enum NODE_TYPE _type) {
  type = _type;
  token = NULL;
  firstChild = NULL;
  parent = NULL;
  nextSibling = NULL;
  prevSibling = NULL;
}

ASTNode::~ASTNode() {
  ASTNode *childNode = NULL, *tempNode = NULL;

  childNode = firstChild;

  while (childNode != NULL) {
    tempNode = childNode->nextSibling;
    delete childNode;
    childNode = tempNode;
  }
}

void ASTNode::Analyse( Scope* ) {
}

void ASTNode::append( ASTNode *child ) {
  ASTNode *lastSibling = this->firstChild;

  child->parent = this;

  if( !this->firstChild ) {
    firstChild = child;
    return;
  }

  // Find the last child node
  while( lastSibling ) {
    if( lastSibling->nextSibling ) {
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
void ASTNode::InsertFirstChild( ASTNode *child ) {
  ASTNode *secondChild;

  child->parent = this;

  if( !firstChild) {
    firstChild = child;
    return;
  }

  secondChild = firstChild;
  firstChild = child;
  secondChild->prevSibling = child;
  child->nextSibling = secondChild;
  return;
}

// Replaces a child node with a new one
void ASTNode::ReplaceChild( ASTNode *childToReplace, ASTNode *newChild ) {
  ASTNode *currentChild = firstChild;
  if( childToReplace == NULL || newChild == NULL ) return;
  
  // Ensure that the childToReplace exists as a child node.
  while( currentChild ) {
    if( currentChild == childToReplace ) break;
    currentChild = currentChild->nextSibling;
  }

  // We may have got to here with currentChild == NULL
  if( currentChild ) {
    newChild->parent = this;

    if( currentChild->prevSibling) {
      currentChild->prevSibling->nextSibling = newChild;
      newChild->prevSibling = currentChild->prevSibling;
    }

    if( currentChild->nextSibling ) {
      currentChild->nextSibling->prevSibling = newChild;
      newChild->nextSibling = currentChild->nextSibling;
    }

    // Modify the first node pointer if we're replacing that.
    if( firstChild == currentChild ) {
      firstChild = newChild;
    }
  }

  return;
}

ASTIterator ASTNode::ChildNodes() {
  return ASTIterator(firstChild);
}

// Recursive function to print a tree of the AST
void ASTNode::print(int depth, int skip, char *prev_cols) {
  ASTIterator end(NULL);
  
  std::cout << NODE_TYPES[type];

  if( token ) {
    std::cout << ":" << token->Content();
  }
  std::cout << "\n";

  for( ASTIterator i = ChildNodes(); i != end; i++) {

    for(int j=0; j < (depth); j++) {
      std::cout << ( prev_cols[j] ? "\u2502" : " ");
    }

    if (i->nextSibling == NULL) {
      std::cout << "\u2514";
      prev_cols[depth] = 0;
      i->print(depth+1, skip+1, prev_cols);
    } else {
      std::cout << "\u251c";
      prev_cols[depth] = 1;
      i->print(depth+1, skip, prev_cols);
    }
  }
}
