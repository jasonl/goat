#include "../ast_node.h"

AddressOperandNode::AddressOperandNode( Token& token ) : OperandNode(ASTNode::AddressOperand) {
  addressString = token.Content();
}

Operand *AddressOperandNode::GenerateOperand() {
  return DispatchOperandFor(addressString, scope->GetSourceFile());
}
