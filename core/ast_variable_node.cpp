#include <string>
#include "ast_node.h"

ASTVariableNode::ASTVariableNode() : ASTNode( ASTNode::Variable ) {
}

void ASTVariableNode::Analyse( Scope *scope ) {
}
