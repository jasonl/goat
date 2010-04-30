#include <string>
#include "ast_node.h"

ASTClassDefinitionNode::ASTClassDefinitionNode( struct _Token *_token) : ASTNode( ASTNode::ClassDefinition ) {
  token = _token;
}

void ASTClassDefinitionNode::Analyse( Scope *scope ) {
}
