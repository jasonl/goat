class ASTConditionalNode : public ASTNode {
public:
  ASTConditionalNode();
  void Analyse( Scope* );
};
