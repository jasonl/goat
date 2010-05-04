#ifndef __AST_PARAMETER_NODE_H
#define __AST_PARAMETER_NODE_H

class ASTParameterNode : public ASTNode {
public:
  ASTParameterNode();
  void Analyse( Scope* );
};

#endif
