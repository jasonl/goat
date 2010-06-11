#include "../ast_node.h"
#include "../lexer.h"

ASTIndirectOperandTermNode::ASTIndirectOperandTermNode( TokenIterator &_token ) : ASTNode( ASTNode::IndirectOperandTerm ) {
  token = &(*_token);
}
