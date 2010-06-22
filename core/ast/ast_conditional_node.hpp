#ifndef __AST_CONDITIONAL_NODE_H
#define __AST_CONDITIONAL_NODE_H

class ASTConditionalNode : public ASTNode {
public:
  ASTConditionalNode();
  void Analyse( Scope* );
  void AddExpression( ASTNode* );
  void AddIfBlock( BlockNode* );
  void AddElseBlock( BlockNode* );
  ASTNode *Expression() { return expression; }
  BlockNode *IfBlock() { return ifBlock; }
  BlockNode *ElseBlock() { return elseBlock; }
private:
  ASTNode *expression;
  BlockNode *elseBlock, *ifBlock;
};

#endif
