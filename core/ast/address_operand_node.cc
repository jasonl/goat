#include "../goat.h"
#include "../ast_node.h"

Operand *AddressOperandNode::GenerateOperand() const {
  Operand *op =  DispatchOperandFor(address, scope->GetSourceFile());
  op->SetSize(size);
  return op;
}
