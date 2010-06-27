#include <cstdlib>
#include "../ast_node.h"
#include "../lexer.h"

ImmediateOperandNode::ImmediateOperandNode( TokenIterator &_token ) : 
  OperandNode( ASTNode::ImmediateOperand ) {
  token = &(*_token);
}

Operand *ImmediateOperandNode::GenerateOperand() {
  return new Operand( atol(Content().c_str()), Operand::Dword );
}
