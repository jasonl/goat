#include <string>
#include "ast_node.h"

ASTSourceFileNode::ASTSourceFileNode() : ASTNode( ASTNode::SourceFile ) {
}

void ASTSourceFileNode::Analyse( Scope *scope ) {
}
