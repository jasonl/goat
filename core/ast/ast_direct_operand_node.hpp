#ifndef __AST_DIRECT_OPERAND_NODE
#define __AST_DIRECT_OPERAND_NODE

class ASTDirectOperandNode : public OperandNode {
public:
  ASTDirectOperandNode( TokenIterator& );
  Operand *GenerateOperand();
};

#endif
