#ifndef __INSTRUCTION_NODE_H
#define __INSTRUCTION_NODE_H

class InstructionNode : public ASTNode {
 public:
 InstructionNode(const std::string &_label, const std::string &_mnemonic) : label(_label), mnemonic(_mnemonic), firstOperand(NULL), lastOperand(NULL) {};
  AssemblyBlock *GenerateCode() const;
  void AppendOperand( OperandNode* );
  OperandIterator Operands() const { return OperandIterator(firstOperand); }
  std::string Print() const { return "Instruction: " + mnemonic; }
#ifdef GOATTEST
  std::string Mnemonic() const { return mnemonic; }
  std::string Label() const { return label; }
#endif

 private:
  const std::string label;
  const std::string mnemonic;
  OperandNode *firstOperand;
  OperandNode *lastOperand;
};

#endif
