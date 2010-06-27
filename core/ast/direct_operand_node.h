#ifndef __DIRECT_OPERAND_NODE
#define __DIRECT_OPERAND_NODE

class DirectOperandNode : public OperandNode {
public:
  DirectOperandNode( TokenIterator& );
  Operand *GenerateOperand();
};

#endif
