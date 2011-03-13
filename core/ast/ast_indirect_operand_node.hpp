#ifndef __AST_INDIRECT_OPERAND_NODE
#define __AST_INDIRECT_OPERAND_NODE

class ASTIndirectOperandNode : public OperandNode {
public:
  ASTIndirectOperandNode( Token& );
  Operand *GenerateOperand();
};

#endif
