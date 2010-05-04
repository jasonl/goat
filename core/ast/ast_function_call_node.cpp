#include "../ast_node.h"

ASTFunctionCallNode::ASTFunctionCallNode() : ASTNode( ASTNode::FunctionCall ) {
}

void ASTFunctionCallNode::Analyse(Scope *scope) {
}
