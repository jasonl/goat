#include "../ast_node.h"
#include "../scope.h"
#include "../lexer.h"

void ImmutableAssignmentNode::Analyse( Scope *_scope ) {
  scope = _scope;

  if(scope->HasVariable(lValue)) {
    // Error
  }

  scope->AddLocalVariable(lValue);

  firstChild->Analyse( scope );
}

void ImmutableAssignmentNode::SetRValue( ASTNode* _rValue ) {
  AppendChild( _rValue );
}

AssemblyBlock *ImmutableAssignmentNode::GenerateCode() const
{
  AssemblyBlock *a = firstChild->GenerateCode();

  a->mov( scope->GeneratePayloadOperand(lValue), eax );
  a->mov( scope->GenerateTypeHashOperand(lValue), ecx );
  a->mov( scope->GenerateDispatchOperand(lValue), edx );

  return a;
}
