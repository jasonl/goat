#include <string>
#include "ast_node.h"

ASTStringLiteralNode::ASTStringLiteralNode() : ASTNode( ASTNode::StringLiteral ) {
}

void ASTStringLiteralNode::Analyse( Scope *scope ) {
}
