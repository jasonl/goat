#include "../ast_node.h"

ASTStringLiteralNode::ASTStringLiteralNode( TokenIterator &_token ) : ASTNode( ASTNode::StringLiteral ) {
  token = &(*_token);
}

void ASTStringLiteralNode::Analyse( Scope *scope ) {
}
