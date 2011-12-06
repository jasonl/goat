#ifndef __AST_FUNCTION_DEF_NODE_H
#define __AST_FUNCTION_DEF_NODE_H

class FunctionDefNode : public ASTNode {
public:
  FunctionDefNode();
  ~FunctionDefNode();
  void Analyse( Scope * );
  ASTIterator ParameterDefs();
  ASTIterator BodyNodes();
  void AddBody( ASTNode* );
  void AddParameterDef( ASTNode* );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *GetAuxiliaryCode();
  std::string Print() const { return "FunctionDef"; }
private:
  AssemblyBlock *bodyAsm;
  ASTNode *body;
};

#endif
