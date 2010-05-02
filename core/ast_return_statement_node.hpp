class ASTReturnStatementNode : public ASTNode {
public:
  ASTReturnStatementNode();
  void SetReturnValue( ASTNode* );
  ASTIterator ChildNodes();
  void Analyse( Scope* );
private:
  ASTNode *returnValue;
};
