#include "../goat.h"
#include "../ast_node.h"
#include "../lexer.h"
#include "../i386/instruction.h"

void OperandNode::AppendOperand(OperandNode *op)
{
	AppendChild(op);

	if (!firstOperand || !lastOperand) {
		firstOperand = op;
		lastOperand = op;
	} else {
		lastOperand->nextOperand = op;
		lastOperand = op;
	}
}
