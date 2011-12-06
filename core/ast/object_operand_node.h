#ifndef __OBJECT_OPERAND_NODE_H
#define __OBJECT_OPERAND_NODE_H

class ObjectOperandNode : public OperandNode {
 public:
  ObjectOperandNode(const std::string &_variable, const std::string &_propertyName) :
	variable(_variable), propertyName(_propertyName) {};
  Operand *GenerateOperand() const;
  std::string Print() const { return "ObjectOperand: " + variable + "." + propertyName; }
 private:
  const std::string variable;
  const std::string propertyName;
};

#endif
