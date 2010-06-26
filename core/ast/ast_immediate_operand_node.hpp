#ifndef __AST_IMMEDIATE_OPERAND_NODE
#define __AST_IMMEDIATE_OPERAND_NODE

class ASTImmediateOperandNode : public OperandNode {
public:
  ASTImmediateOperandNode( TokenIterator& );
};

#endif
