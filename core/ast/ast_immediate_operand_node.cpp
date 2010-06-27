#include <cstdlib>
#include "../ast_node.h"
#include "../lexer.h"

ASTImmediateOperandNode::ASTImmediateOperandNode( TokenIterator &_token ) : 
  OperandNode( ASTNode::ImmediateOperand ) {
  token = &(*_token);
}

Operand *ASTImmediateOperandNode::GenerateOperand() {
  return new Operand( atol(Content().c_str()), Operand::Dword );
}
