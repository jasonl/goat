class ASTNullLiteralNode : public ASTNode {
public:
  ASTNullLiteralNode();
  void Analyse( Scope* );
};
