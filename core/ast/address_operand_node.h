#ifndef __ADDRESS_OPERAND_NODE_H
#define __ADDRESS_OPERAND_NODE_H

class AddressOperandNode : public OperandNode {
 public:
  AddressOperandNode( Token& );
  Operand *GenerateOperand();
 private:
  std::string addressString;
};


#endif
