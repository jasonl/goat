#include "../goat.h"
#include "../ast_node.h"

// An ASTNode corresponding to a return statement. It has exactly one child
// node - either the return expression, or an Null literal.
void ReturnStatementNode::SetReturnValue( ASTNode *_returnValue ) {
  AppendChild(_returnValue);
  returnValue = _returnValue;
}

ASTIterator ReturnStatementNode::ChildNodes() const
{
  return ASTIterator(returnValue);
}

void ReturnStatementNode::Analyse( Scope *_scope ) {
  scope = _scope;
  if(returnValue) returnValue->Analyse( scope );
}

void ReturnStatementNode::GenerateCode(AssemblyBlock*a) const
{
	returnValue->GenerateCode(a);
	a->mov(esp, ebp);
	a->pop(ebp);
	a->ret();
}
