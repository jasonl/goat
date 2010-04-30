class ASTMutableAssignmentNode : public ASTNode {
public:
  ASTMutableAssignmentNode( struct _Token* );
  void Analyse( Scope * );
};
