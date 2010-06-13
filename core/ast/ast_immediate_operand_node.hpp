#ifndef __AST_IMMEDIATE_OPERAND_NODE
#define __AST_IMMEDIATE_OPERAND_NODE

class ASTImmediateOperandNode : public ASTNode {
public:
  ASTImmediateOperandNode( TokenIterator& );
};

#endif
