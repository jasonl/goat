#ifndef __AST_RETURN_STATEMENT_NODE_H
#define __AST_RETURN_STATEMENT_NODE_H

class ASTReturnStatementNode : public ASTNode {
public:
  ASTReturnStatementNode();
  void SetReturnValue( ASTNode* );
  ASTIterator ChildNodes();
  void Analyse( Scope* );
private:
  ASTNode *returnValue;
};

#endif
