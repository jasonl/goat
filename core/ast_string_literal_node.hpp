class ASTStringLiteralNode : public ASTNode {
public:
  ASTStringLiteralNode();
  void Analyse( Scope * );
};
