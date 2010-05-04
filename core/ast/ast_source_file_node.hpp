#ifndef __AST_SOURCE_FILE_NODE_H
#define __AST_SOURCE_FILE_NODE_H

class ASTSourceFileNode : public ASTNode {
public:
  ASTSourceFileNode();
  void Analyse( Scope* );
};

#endif
