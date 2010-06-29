#ifndef __INLINE_ASSEMBLY_NODE_H
#define __INLINE_ASSEMBLY_NODE_H

class InlineAssemblyNode : public ASTNode {
 public:
  InlineAssemblyNode();
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
};

#endif
