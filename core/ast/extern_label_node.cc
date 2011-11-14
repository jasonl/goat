#include "../ast_node.h"
#include "../source_file.h"

Operand *ExternLabelNode::GenerateOperand() const
{
	scope->GetSourceFile()->AddExternSymbol(content);
	return new Operand(content);
}
