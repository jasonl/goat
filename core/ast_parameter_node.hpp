class ASTParameterNode : public ASTNode {
public:
  ASTParameterNode();
  void Analyse( Scope* );
};
