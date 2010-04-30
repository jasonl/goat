class ASTImmutableAssignmentNode : public ASTNode {
public:
  ASTImmutableAssignmentNode( struct _Token* );
  void Analyse( Scope * );
};
