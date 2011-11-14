#ifndef __DIRECT_OPERAND_NODE
#define __DIRECT_OPERAND_NODE

class DirectOperandNode : public OperandNode {
public:
 DirectOperandNode(const std::string &_reg) : OperandNode(DirectOperand), reg(_reg) {};
  Operand *GenerateOperand() const;
  std::string PrintableIdentifier() { return ": " + reg; }
#ifdef GOATTEST
  std::string Register() const { return reg; }
#endif

 private:
  const std::string reg;
};

#endif
