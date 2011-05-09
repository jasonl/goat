#include "../ast_node.h"

void MutableAssignmentNode::Analyse( Scope *_scope ) {
  scope = _scope;

  if(!scope->HasVariable(lValue)) {
    scope->AddLocalVariable(lValue);
  }

  firstChild->Analyse( scope );
}

void MutableAssignmentNode::SetRValue( ASTNode *_rValue ) {
  AppendChild( _rValue );
}

AssemblyBlock *MutableAssignmentNode::GenerateCode() const
{
  AssemblyBlock *a = firstChild->GenerateCode();

  a->mov( scope->GeneratePayloadOperand(lValue), eax );
  a->mov( scope->GenerateTypeHashOperand(lValue), ecx );
  a->mov( scope->GenerateDispatchOperand(lValue), edx );

  a->CommentLastInstruction("Assignment to " + lValue);

  return a;
}
