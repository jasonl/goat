class ASTIntegerLiteralNode : public ASTNode {
public:
  ASTIntegerLiteralNode( struct _Token *);
  void Analyse( Scope * );
};
