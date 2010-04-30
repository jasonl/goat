class ASTClassDefinitionNode : public ASTNode {
public:
  ASTClassDefinitionNode( struct _Token* );
  void Analyse( Scope* );
};
