#include <cstdlib>
#include "../ast_node.h"

Operand *ImmediateOperandNode::GenerateOperand() const
{
	Operand *op = new Operand( atol(content.c_str()), Operand::Dword );
	op->SetSize(size);
	return op;
}
