#include "../goat.h"
#include "../ast_node.h"

Operand *ObjectOperandNode::GenerateOperand() const
{
	Operand *op = NULL;

	if(!scope->HasVariable(variable))
	{
		goatError(0, "No variable found in local scope");
		return NULL;
	}

	if(propertyName == "payload")
		op = &(scope->GeneratePayloadOperand(variable));

	if(propertyName == "dispatch")
		op = &(scope->GenerateDispatchOperand(variable));

	if(propertyName == "type")
		op = &(scope->GenerateTypeHashOperand(variable));

	if(op) {
		op->SetSize(size);
		return op;
	}

	goatError(0, "Invalid object property found in inline assembly");
	return NULL;
}
