#ifndef __INSTRUCTION_NODE_H
#define __INSTRUCTION_NODE_H

class InstructionNode : public ASTNode {
 public:
 InstructionNode(const std::string &_label, const std::string &_mnemonic) : ASTNode(Instruction), label(_label), mnemonic(_mnemonic), firstOperand(NULL), lastOperand(NULL) {};
  AssemblyBlock *GenerateCode();
  void AppendOperand( OperandNode* );
  OperandIterator Operands() { return OperandIterator(firstOperand); }
 private:
  const std::string label;
  const std::string mnemonic;
  OperandNode *firstOperand;
  OperandNode *lastOperand;
};

#endif
