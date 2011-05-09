#include "../ast_node.h"

Operand *AddressOperandNode::GenerateOperand() const {
  return DispatchOperandFor(address, scope->GetSourceFile());
}
