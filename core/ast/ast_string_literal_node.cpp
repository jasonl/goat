#include "../ast_node.h"

ASTStringLiteralNode::ASTStringLiteralNode( std::string _identifier ) : ASTNode( ASTNode::StringLiteral ) {
  identifier = _identifier;
}

void ASTStringLiteralNode::Analyse( Scope *scope ) {
}
