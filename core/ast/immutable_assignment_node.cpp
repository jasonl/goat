#include "../ast_node.h"
#include "../scope.h"
#include "../lexer.h"

ImmutableAssignmentNode::ImmutableAssignmentNode( TokenIterator &_token): 
  ASTNode( ASTNode::ImmutableAssignment ) {
  token = &(*_token);
}

void ImmutableAssignmentNode::Analyse( Scope *_scope ) {
  scope = _scope;
  
  if(scope->HasVariable( Content() )) {
    // Error
  }

  scope->AddLocalVariable( Content() );
  
  rValue->Analyse( scope );  
}

void ImmutableAssignmentNode::SetRValue( ASTNode* _rValue ) {
  AppendChild( _rValue );
  rValue = _rValue;
}

ASTIterator ImmutableAssignmentNode::ChildNodes() {
  return ASTIterator(rValue);
}

AssemblyBlock *ImmutableAssignmentNode::GenerateCode() {
  AssemblyBlock *a = rValue->GenerateCode();

  a->MOV( scope->GeneratePayloadOperand(Content()), eax );
  a->MOV( scope->GenerateTypeHashOperand(Content()), ecx );
  a->MOV( scope->GenerateDispatchOperand(Content()), edx );

  return a;
}
