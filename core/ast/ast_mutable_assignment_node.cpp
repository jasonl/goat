#include "../ast_node.h"

ASTMutableAssignmentNode::ASTMutableAssignmentNode( TokenIterator &_token) : ASTNode( ASTNode::MutableAssignment ) {
  token = &(*_token);
}

void ASTMutableAssignmentNode::Analyse( Scope *_scope ) {
  scope = _scope;
  
  if(!scope->HasVariable( Content() )) {
    scope->AddLocalVariable( Content() );
  }
  
  rValue->Analyse( scope );  
}

void ASTMutableAssignmentNode::SetRValue( ASTNode *_rValue ) {
  rValue = _rValue;
  firstChild = _rValue;
}
