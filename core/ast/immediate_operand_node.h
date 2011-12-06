#ifndef __IMMEDIATE_OPERAND_NODE
#define __IMMEDIATE_OPERAND_NODE

class ImmediateOperandNode : public OperandNode {
public:
 ImmediateOperandNode(const std::string &_content) : content(_content) {};
  Operand *GenerateOperand() const;
  std::string Print() const { return "ImmediateOperand: " + content; }

#ifdef GOATTEST
  const std::string Content() const { return content; }
#endif
 private:
  const std::string content;
};

#endif
