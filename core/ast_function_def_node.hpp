class ASTFunctionDefNode : public ASTNode {
public:
  ASTFunctionDefNode();
  void Analyse( Scope * );
};
