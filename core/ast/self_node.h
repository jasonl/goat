class SelfNode : public ASTNode {
public:
  SelfNode();
  void Analyse( Scope * );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
};
