#include "../ast_node.h"

MutableAssignmentNode::MutableAssignmentNode( TokenIterator &_token): 
  ASTNode( ASTNode::MutableAssignment ) {
  token = &(*_token);
}

void MutableAssignmentNode::Analyse( Scope *_scope ) {
  scope = _scope;
  
  if(!scope->HasVariable( Content() )) {
    scope->AddLocalVariable( Content() );
  }
  
  rValue->Analyse( scope );  
}

void MutableAssignmentNode::SetRValue( ASTNode *_rValue ) {
  AppendChild( _rValue );
  rValue = _rValue;
}

AssemblyBlock *MutableAssignmentNode::GenerateCode() {
  AssemblyBlock *a = rValue->GenerateCode();

  a->MOV( scope->GeneratePayloadOperand(Content()), eax );
  a->MOV( scope->GenerateTypeHashOperand(Content()), ecx );
  a->MOV( scope->GenerateDispatchOperand(Content()), edx );

  return a;
}
