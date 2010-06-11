#include "../ast_node.h"
#include "../lexer.h"

ASTIndirectOperandNode::ASTIndirectOperandNode( TokenIterator &_token ) : ASTNode( ASTNode::IndirectOperand ) {
  token = &(*_token);
}
