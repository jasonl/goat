#include "../goat.h"
#include "../ast_node.h"

Operand *ObjectOperandNode::GenerateOperand() const
{
  if(!scope->HasVariable(variable))
  {
    goatError(0, "No variable found in local scope");
	return NULL;
  }

  if(propertyName == "payload")
    return &(scope->GeneratePayloadOperand(variable));

  if(propertyName == "dispatch")
    return &(scope->GenerateDispatchOperand(variable));

  if(propertyName == "type")
    return &(scope->GenerateTypeHashOperand(variable));

  goatError(0, "Invalid object property found in inline assembly");
  return NULL;
}
