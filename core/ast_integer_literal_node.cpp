#include <string>
#include "ast_node.h"

ASTIntegerLiteralNode::ASTIntegerLiteralNode() : ASTNode( ASTNode::IntegerLiteral ) {
}

void ASTIntegerLiteralNode::Analyse( Scope *scope ) {
}
