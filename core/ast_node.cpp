#include "lexer.h"
#include "ast.h"

ASTNode::ASTNode( enum NODE_TYPE _type) {
  type = _type;
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

void ASTNode::append( ASTNode *child ) {
  ASTNode *lastSibling = this->firstChild;

  child->parent = this;

  if( !(int)firstChild ) {
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
