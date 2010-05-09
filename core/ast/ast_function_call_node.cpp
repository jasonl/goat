#include "../ast_node.h"

ASTFunctionCallNode::ASTFunctionCallNode( TokenIterator &_token ) : ASTNode( ASTNode::FunctionCall ) {
  token = &(*_token);
}

void ASTFunctionCallNode::Analyse(Scope *scope) {
}
