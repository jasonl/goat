#ifndef __BLOCK_NODE_H
#define __BLOCK_NODE_H

class BlockNode : public ASTNode {
 public:
  BlockNode();
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
};

#endif