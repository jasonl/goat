#include <string>
#include "ast_node.h"

ASTMutableAssignmentNode::ASTMutableAssignmentNode( struct _Token *_token) : ASTNode( ASTNode::MutableAssignment ) {
  token = _token;
}

void ASTMutableAssignmentNode::Analyse( Scope *scope ) {
}
