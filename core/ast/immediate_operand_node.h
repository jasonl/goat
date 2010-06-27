#ifndef __IMMEDIATE_OPERAND_NODE
#define __IMMEDIATE_OPERAND_NODE

class ImmediateOperandNode : public OperandNode {
public:
  ImmediateOperandNode( TokenIterator& );
  Operand *GenerateOperand();
};

#endif
