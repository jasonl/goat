#include "../ast_node.h"

StringLiteralNode::StringLiteralNode( Token &_token ) : ASTNode( ASTNode::StringLiteral ) {
  token = &_token;
}

void StringLiteralNode::Analyse( Scope *scope ) {
}
