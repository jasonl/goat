#include <string>
#include "ast_node.h"

ASTReturnStatementNode::ASTReturnStatementNode() : ASTNode( ASTNode::ReturnStatement ) {
}

void ASTReturnStatementNode::Analyse( Scope *scope ) {
}
