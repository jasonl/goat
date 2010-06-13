#include "../ast_node.h"
#include "../lexer.h"

ASTLabelNode::ASTLabelNode( TokenIterator &_token ): 
  ASTNode( ASTNode::Label ) {
  token = &(*_token);
}
