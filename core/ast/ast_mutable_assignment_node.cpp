#include "../ast_node.h"

ASTMutableAssignmentNode::ASTMutableAssignmentNode( TokenIterator &_token) : ASTNode( ASTNode::MutableAssignment ) {
  token = &(*_token);
}

void ASTMutableAssignmentNode::Analyse( Scope *scope ) {
}

void ASTMutableAssignmentNode::SetRValue( ASTNode *_rValue ) {
  rValue = _rValue;
  firstChild = _rValue;
}
