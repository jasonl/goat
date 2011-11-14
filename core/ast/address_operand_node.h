#ifndef __ADDRESS_OPERAND_NODE_H
#define __ADDRESS_OPERAND_NODE_H

class AddressOperandNode : public OperandNode {
 public:
 AddressOperandNode( const std::string &_address ) : OperandNode(AddressOperand), address(_address) {};
  Operand *GenerateOperand() const;
  std::string PrintableIdentifier() { return ": " + address; }
 private:
  const std::string address;
};


#endif
