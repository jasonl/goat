#include "../goat.h"
#include "../ast_node.h"
#include "../lexer.h"

Operand *IndirectOperandTermNode::ModifyOperand(Operand* op) const
{
	IntegerLiteralNode *i = dynamic_cast<IntegerLiteralNode*>(firstChild);

	if (i) {
		uint32_t val = i->Value();

		switch (operation[0]) {
		case '-':
			return &(*op - val);
			break;
		case '+':
			return &(*op + val);
			break;
		case '*':
			return &(*op * val);
			break;
		}
	}

	return op;
}
