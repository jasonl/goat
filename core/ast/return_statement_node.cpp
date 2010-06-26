#include "../ast_node.h"

// An ASTNode corresponding to a return statement. It has exactly one child
// node - either the return expression, or an Null literal.

ReturnStatementNode::ReturnStatementNode() : ASTNode( ASTNode::ReturnStatement ) {
}

void ReturnStatementNode::SetReturnValue( ASTNode *_returnValue ) {
  returnValue = _returnValue;
  firstChild = _returnValue; // Required for tests
}

ASTIterator ReturnStatementNode::ChildNodes() {
  return ASTIterator( returnValue );
}

void ReturnStatementNode::Analyse( Scope *_scope ) {
  scope = _scope;
  if(returnValue) returnValue->Analyse( scope );
}

AssemblyBlock *ReturnStatementNode::GenerateCode() {
  AssemblyBlock *a = returnValue->GenerateCode();
  a->POP(ebp);
  a->RET();
  return a;
}

