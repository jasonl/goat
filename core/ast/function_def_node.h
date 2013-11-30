#ifndef __AST_FUNCTION_DEF_NODE_H
#define __AST_FUNCTION_DEF_NODE_H

class FunctionDefNode : public ASTNode {
public:
  FunctionDefNode();
  ~FunctionDefNode();
  void Analyse( Scope * );
  ASTIterator ParameterDefs() const;
  ASTIterator BodyNodes() const;
  void AddBody( ASTNode* );
  void AddParameterDef( ASTNode* );
  int ParameterCount() const { return paramCount; }
  void GenerateCode(AssemblyBlock*) const;
  void GetAuxiliaryCode(AssemblyBlock*) const;
  std::string Print() const { return "FunctionDef"; }
private:
  ASTNode *body;
  int paramCount;
  std::string functionName;
};

#endif
