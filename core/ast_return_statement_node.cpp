#include <string>
#include "ast_node.h"

// An ASTNode corresponding to a return statement. It has exactly one child
// node - either the return expression, or an Null literal.

ASTReturnStatementNode::ASTReturnStatementNode() : ASTNode( ASTNode::ReturnStatement ) {
}

void ASTReturnStatementNode::SetReturnValue( ASTNode *_returnValue ) {
  returnValue = _returnValue;
  firstChild = _returnValue; // Required for tests
}

ASTIterator ASTReturnStatementNode::ChildNodes() {
  return ASTIterator( returnValue );
}

void ASTReturnStatementNode::Analyse( Scope *_scope ) {
  scope = _scope;
  if(returnValue) returnValue->Analyse( scope );
}


