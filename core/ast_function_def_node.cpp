#include <string>
#include "ast_node.h"

ASTFunctionDefNode::ASTFunctionDefNode() : ASTNode( ASTNode::FunctionDef ) {
}

void ASTFunctionDefNode::Analyse( Scope *scope ) {
}
