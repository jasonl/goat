#include "../ast_node.h"

ASTIntegerLiteralNode::ASTIntegerLiteralNode( struct _Token *_token ) : ASTNode( ASTNode::IntegerLiteral ) {
  token = _token;
}

void ASTIntegerLiteralNode::Analyse( Scope *scope ) {
}
