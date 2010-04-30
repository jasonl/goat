class ASTIntegerLiteralNode : public ASTNode {
public:
  ASTIntegerLiteralNode();
  void Analyse( Scope * );
};
