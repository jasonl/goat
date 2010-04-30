#include <string>
#include "ast_node.h"

ASTConditionalNode::ASTConditionalNode() : ASTNode( ASTNode::Conditional ) {
}

void ASTConditionalNode::Analyse( Scope *scope ) {
}
