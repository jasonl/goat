class ASTConditionalNode : public ASTNode {
public:
  ASTConditionalNode();
  void Analyse( Scope* );
  void AddExpression( ASTNode* );
  void AddIfBlock( ASTBlockNode* );
  void AddElseBlock( ASTBlockNode* );
  ASTNode *Expression() { return expression; }
  ASTBlockNode *IfBlock() { return ifBlock; }
  ASTBlockNode *ElseBlock() { return elseBlock; }
private:
  ASTNode *expression;
  ASTBlockNode *elseBlock, *ifBlock;
};
