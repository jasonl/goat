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
  
  firstChild->Analyse( scope );  
}

void ImmutableAssignmentNode::SetRValue( ASTNode* _rValue ) {
  AppendChild( _rValue );
}

ASTIterator ImmutableAssignmentNode::ChildNodes() {
  return ASTIterator(firstChild);
}

AssemblyBlock *ImmutableAssignmentNode::GenerateCode() {
  AssemblyBlock *a = firstChild->GenerateCode();

  a->mov( scope->GeneratePayloadOperand(Content()), eax );
  a->mov( scope->GenerateTypeHashOperand(Content()), ecx );
  a->mov( scope->GenerateDispatchOperand(Content()), edx );

  return a;
}
