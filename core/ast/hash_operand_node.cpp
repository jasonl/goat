#include "../ast_node.h"

HashOperandNode::HashOperandNode( Token& token) : OperandNode(ASTNode::HashOperand) {
  hashString = token.Content();
}

Operand *HashOperandNode::GenerateOperand() {
  return new Operand(goatHash(hashString), Operand::Dword);
}
