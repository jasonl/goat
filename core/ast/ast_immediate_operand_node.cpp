#include "../ast_node.h"
#include "../lexer.h"

ASTImmediateOperandNode::ASTImmediateOperandNode( TokenIterator &_token ) : 
  OperandNode( ASTNode::ImmediateOperand ) {
  token = &(*_token);
}
