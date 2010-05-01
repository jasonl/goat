class ASTImmutableAssignmentNode : public ASTNode {
public:
  ASTImmutableAssignmentNode( struct _Token* );
  void Analyse( Scope* );
  void SetRValue( ASTNode* );
  ASTIterator ChildNodes();
private:
  ASTNode *rValue;
};
