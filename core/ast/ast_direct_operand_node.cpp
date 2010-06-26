#include "../ast_node.h"
#include "../lexer.h"

ASTDirectOperandNode::ASTDirectOperandNode( TokenIterator &_token ): 
  OperandNode( ASTNode::DirectOperand ) {
  token = &(*_token);
}

Operand *ASTDirectOperandNode::GenerateOperand() {
  return NULL;
}
