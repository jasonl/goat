#include "../ast_node.h"

ASTIntegerLiteralNode::ASTIntegerLiteralNode( TokenIterator &_token ) : ASTNode( ASTNode::IntegerLiteral ) {
  token = &(*_token);
}

void ASTIntegerLiteralNode::Analyse( Scope *_scope ) {
  scope = _scope;
}
