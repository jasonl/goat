#ifndef __EXTERN_LABEL_NODE
#define __EXTERN_LABEL_NODE

class ExternLabelNode : public OperandNode {
public:
 ExternLabelNode(const std::string &_content) : OperandNode(), content(_content) {};
  Operand *GenerateOperand() const;
  std::string Print() const { return "ExternalLabel: " + content; }
 private:
  const std::string content;
};

#endif
