#include "../ast_node.h"

ASTFunctionCallNode::ASTFunctionCallNode( std::string _identifier) : ASTNode( ASTNode::FunctionCall ) {
  identifier = _identifier;
}

void ASTFunctionCallNode::Analyse(Scope *scope) {
}
