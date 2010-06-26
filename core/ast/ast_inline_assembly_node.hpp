#ifndef __AST_INLINE_ASSEMBLY_NODE_H
#define __AST_INLINE_ASSEMBLY_NODE_H

class ASTInlineAssemblyNode : public ASTNode {
 public:
  ASTInlineAssemblyNode();
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
};

#endif
