class ASTStringLiteralNode : public ASTNode {
public:
  ASTStringLiteralNode( struct _Token * );
  void Analyse( Scope * );
};
