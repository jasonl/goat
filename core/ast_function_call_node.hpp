class ASTFunctionCallNode : public ASTNode {
public:
  ASTFunctionCallNode();
  void Analyse( Scope* );
};
