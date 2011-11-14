#ifndef __INDIRECT_OPERAND_NODE
#define __INDIRECT_OPERAND_NODE

class IndirectOperandNode : public OperandNode {
 public:
  IndirectOperandNode(const std::string &_reg) : OperandNode(IndirectOperand), reg(_reg) {};
  Operand *GenerateOperand() const;
  std::string PrintableIdentifier() { return ": " + reg; }
#ifdef GOATTEST
  std::string Register() const { return reg; }
#endif

 private:
  const std::string reg;
};

#endif
