#ifndef __IMMEDIATE_OPERAND_NODE
#define __IMMEDIATE_OPERAND_NODE

class ImmediateOperandNode : public OperandNode {
public:
 ImmediateOperandNode(const std::string &_content) : OperandNode(ImmediateOperand), content(_content) {};
  Operand *GenerateOperand() const;
 private:
  const std::string content;
};

#endif
