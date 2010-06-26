#ifndef __INSTRUCTION_NODE
#define __INSTRUCTION_NODE

class InstructionNode : public ASTNode {
  OperandNode *firstChild;
public:
  InstructionNode( TokenIterator& );
  AssemblyBlock *GenerateCode();
  OperandIterator Operands() { return OperandIterator(firstChild); }
};

#endif
