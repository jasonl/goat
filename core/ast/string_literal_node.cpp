#include "../ast_node.h"

StringLiteralNode::StringLiteralNode( TokenIterator &_token ) : ASTNode( ASTNode::StringLiteral ) {
  token = &(*_token);
}

void StringLiteralNode::Analyse( Scope *scope ) {
}
