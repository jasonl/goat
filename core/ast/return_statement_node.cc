#include "../ast_node.h"

// An ASTNode corresponding to a return statement. It has exactly one child
// node - either the return expression, or an Null literal.
void ReturnStatementNode::SetReturnValue( ASTNode *_returnValue ) {
  AppendChild(_returnValue);
  returnValue = _returnValue;
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
  a->add( esp, *new Operand(scope->GetLocalVariableCount() * 12));
  a->mov( esp, ebp );
  a->pop( ebp );
  a->ret();
  return a;
}


