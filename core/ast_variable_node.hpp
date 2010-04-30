class ASTVariableNode : public ASTNode {
public:
  ASTVariableNode();
  void Analyse( Scope *scope );
};
