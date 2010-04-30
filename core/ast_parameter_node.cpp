#include <string>
#include "ast_node.h"

ASTParameterNode::ASTParameterNode() : ASTNode( ASTNode::Parameter ) {
}

void ASTParameterNode::Analyse( Scope *scope ) {
}
