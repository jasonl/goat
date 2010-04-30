#include <string>
#include "ast_node.h"

ASTStringLiteralNode::ASTStringLiteralNode( struct _Token *_token) : ASTNode( ASTNode::StringLiteral ) {
  token = _token;
}

void ASTStringLiteralNode::Analyse( Scope *scope ) {
}
