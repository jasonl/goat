#include "../ast_node.h"

Operand *HashOperandNode::GenerateOperand() const
{
  return new Operand(goatHash(hashString), Operand::Dword);
}
