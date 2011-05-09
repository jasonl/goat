#include <cstdlib>
#include "../ast_node.h"

Operand *ImmediateOperandNode::GenerateOperand() const
{
  return new Operand( atol(content.c_str()), Operand::Dword );
}
