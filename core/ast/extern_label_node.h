#ifndef __EXTERN_LABEL_NODE
#define __EXTERN_LABEL_NODE

class ExternLabelNode : public OperandNode {
public:
 ExternLabelNode(const std::string &_content) : OperandNode(ExternLabel), content(_content) {};
  Operand *GenerateOperand() const;
 private:
  const std::string content;
};

#endif
