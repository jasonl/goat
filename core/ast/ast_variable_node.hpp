#ifndef __AST_VARIABLE_NODE_H
#define __AST_VARIABLE_NODE_H

class ASTVariableNode : public ASTNode {
public:
  ASTVariableNode( TokenIterator& );
  void Analyse( Scope* );
};

#endif