#ifndef __OBJECT_OPERAND_NODE_H
#define __OBJECT_OPERAND_NODE_H

class ObjectOperandNode : public OperandNode {
 public:
  ObjectOperandNode( Token& );
  void SetPropertyName( std::string );
  Operand *GenerateOperand();
 private:
  std::string propertyName;
};

#endif
