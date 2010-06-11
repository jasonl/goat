#ifndef __AST_INDIRECT_OPERAND_NODE
#define __AST_INDIRECT_OPERAND_NODE

class ASTIndirectOperandNode : public ASTNode {
public:
  ASTIndirectOperandNode( TokenIterator& );
};

#endif
