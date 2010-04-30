class ASTSourceFileNode : public ASTNode {
public:
  ASTSourceFileNode();
  void Analyse( Scope* );
};
