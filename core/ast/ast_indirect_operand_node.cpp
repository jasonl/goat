#include "../ast_node.h"
#include "../lexer.h"

ASTIndirectOperandNode::ASTIndirectOperandNode( TokenIterator &_token ) : OperandNode( ASTNode::IndirectOperand ) {
  token = &(*_token);
}
