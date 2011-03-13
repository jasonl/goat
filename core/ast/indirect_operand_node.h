#ifndef __INDIRECT_OPERAND_NODE
#define __INDIRECT_OPERAND_NODE

class IndirectOperandNode : public OperandNode {
public:
  IndirectOperandNode( Token& );
  Operand *GenerateOperand();
};

#endif
