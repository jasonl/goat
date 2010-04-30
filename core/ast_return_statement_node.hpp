class ASTReturnStatementNode : public ASTNode {
public:
  ASTReturnStatementNode();
  void Analyse( Scope* );
};
