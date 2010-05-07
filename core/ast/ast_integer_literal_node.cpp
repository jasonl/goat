#include "../ast_node.h"

ASTIntegerLiteralNode::ASTIntegerLiteralNode( std::string _identifier ) : ASTNode( ASTNode::IntegerLiteral ) {
  identifier = _identifier;
}

void ASTIntegerLiteralNode::Analyse( Scope *scope ) {
}
