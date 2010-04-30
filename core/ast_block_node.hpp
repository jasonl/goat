class ASTBlockNode : public ASTNode {
 public:
  ASTBlockNode();
  void Analyse( Scope* );
};
