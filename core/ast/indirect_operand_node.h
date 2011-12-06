#ifndef __INDIRECT_OPERAND_NODE
#define __INDIRECT_OPERAND_NODE

class IndirectOperandNode : public OperandNode {
 public:
  IndirectOperandNode(const std::string &_reg) : OperandNode(), reg(_reg) {};
  Operand *GenerateOperand() const;
  std::string Print() const { return "IndirectOperand: " + reg; }
#ifdef GOATTEST
  std::string Register() const { return reg; }
#endif

 private:
  const std::string reg;
};

#endif
