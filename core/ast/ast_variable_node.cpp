#include "../ast_node.h"

ASTVariableNode::ASTVariableNode( TokenIterator & _token ) : ASTNode( ASTNode::Variable ) {
  token = &(*_token);
}

void ASTVariableNode::Analyse( Scope *scope ) {
}
