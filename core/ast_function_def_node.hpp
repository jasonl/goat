class ASTFunctionDefNode : public ASTNode {
public:
  ASTFunctionDefNode();
  void Analyse( Scope * );
  ASTIterator ParameterDefs();
  void AddBody( ASTNode* );
  void AddParameterDef( ASTNode* );
private:
  ASTNode *body;
};
