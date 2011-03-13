#include "../ast_node.h"
#include "../lexer.h"

IndirectOperandTermNode::IndirectOperandTermNode( Token &_token ) : ASTNode( ASTNode::IndirectOperandTerm ) {
  token = &_token;
}
