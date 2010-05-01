#include <string>
#include "ast_node.h"

ASTImmutableAssignmentNode::ASTImmutableAssignmentNode( struct _Token *_token) : ASTNode( ASTNode::ImmutableAssignment ) {
  token = _token;
}

void ASTImmutableAssignmentNode::Analyse( Scope *scope ) {
}

void ASTImmutableAssignmentNode::SetRValue( ASTNode* _rValue ) {
  rValue = _rValue;
}

ASTIterator ASTImmutableAssignmentNode::ChildNodes() {
  return ASTIterator(rValue);
}
