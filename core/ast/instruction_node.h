#ifndef __INSTRUCTION_NODE
#define __INSTRUCTION_NODE

class InstructionNode : public ASTNode {
  OperandNode *firstOperand;
  OperandNode *lastOperand;
public:
  InstructionNode( TokenIterator& );
  AssemblyBlock *GenerateCode();
  void AppendOperand( OperandNode* );
  OperandIterator Operands() { return OperandIterator(firstOperand); }
};

#endif
