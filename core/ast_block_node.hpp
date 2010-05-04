#ifndef __AST_BLOCK_NODE_H
#define __AST_BLOCK_NODE_H

class ASTBlockNode : public ASTNode {
 public:
  ASTBlockNode();
  void Analyse( Scope* );
};

#endif
