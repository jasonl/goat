#include "../ast_node.h"
#include "../lexer.h"

ASTOperandNode::ASTOperandNode( TokenIterator &_token ) : ASTNode( ASTNode::Operand ) {
  token = &(*_token);
}
