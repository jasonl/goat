#ifndef __AST_FUNCTION_DEF_NODE_H
#define __AST_FUNCTION_DEF_NODE_H

class ASTFunctionDefNode : public ASTNode {
public:
  ASTFunctionDefNode();
  ~ASTFunctionDefNode();
  void Analyse( Scope * );
  ASTIterator ParameterDefs();
  void AddBody( ASTNode* );
  void AddParameterDef( ASTNode* );
private:
  ASTNode *body;
};

#endif
