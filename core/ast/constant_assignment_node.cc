#include "../goat.h"
#include "../ast_node.h"
#include "../scope.h"
#include "../lexer.h"

void ConstantAssignmentNode::Analyse( Scope *_scope ) {
  scope = _scope;

  if(scope->HasVariable(lValue)) {
    // Error
  }

  scope->AddLocalVariable(lValue);

  firstChild->Analyse( scope );
}

void ConstantAssignmentNode::SetRValue( ASTNode* _rValue ) {
  AppendChild( _rValue );
}

void ConstantAssignmentNode::GenerateCode(AssemblyBlock* a) const
{
  firstChild->GenerateCode(a);
  a->mov(scope->GeneratePayloadOperand(lValue), eax);
  a->mov(scope->GenerateTypeHashOperand(lValue), ecx);
  a->mov(scope->GenerateDispatchOperand(lValue), edx);
}
