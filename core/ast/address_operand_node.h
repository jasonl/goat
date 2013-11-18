#ifndef __ADDRESS_OPERAND_NODE_H
#define __ADDRESS_OPERAND_NODE_H

class AddressOperandNode : public OperandNode {
 public:
 AddressOperandNode( const std::string &_address ) : address(_address) {};
  Operand *GenerateOperand() const;
  std::string Print() const { return "AddressOperand: " + address; }
 private:
  const std::string address;
};


#endif
