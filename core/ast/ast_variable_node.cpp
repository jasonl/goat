#include "../ast_node.h"

ASTVariableNode::ASTVariableNode( std::string _identifier) : ASTNode( ASTNode::Variable ) {
  identifier = _identifier;
}

void ASTVariableNode::Analyse( Scope *scope ) {
}
