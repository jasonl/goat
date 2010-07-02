#include "../ast_node.h"
#include "../scope.h"
#include "../lexer.h"

ASTImmutableAssignmentNode::ASTImmutableAssignmentNode( TokenIterator &_token) : ASTNode( ASTNode::ImmutableAssignment ) {
  token = &(*_token);
}

void ASTImmutableAssignmentNode::Analyse( Scope *_scope ) {
  scope = _scope;
  
  if(scope->HasVariable( Content() )) {
    // Error
  }

  scope->AddLocalVariable( Content() );
  
  rValue->Analyse( scope );  
}

void ASTImmutableAssignmentNode::SetRValue( ASTNode* _rValue ) {
  rValue = _rValue;
  firstChild = _rValue; // Required for tests
}

ASTIterator ASTImmutableAssignmentNode::ChildNodes() {
  return ASTIterator(rValue);
}
