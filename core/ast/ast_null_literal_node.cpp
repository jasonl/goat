#include "../ast_node.h"

ASTNullLiteralNode::ASTNullLiteralNode() : ASTNode( ASTNode::NullLiteral ) {
}

void ASTNullLiteralNode::Analyse( Scope *_scope ) {
  scope = _scope;
}
