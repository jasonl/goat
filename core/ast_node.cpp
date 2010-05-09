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

  if( !(int)this->firstChild ) {
    firstChild = child;
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
void ASTNode::InsertFirstChild( ASTNode *child ) {
  ASTNode *secondChild;

  child->parent = this;

  if( !(int)this->firstChild) {
    this->firstChild = child;
    return;
  }

  secondChild = this->firstChild;
  this->firstChild = child;
  secondChild->prevSibling = child;
  child->nextSibling = secondChild;
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
