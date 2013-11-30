#ifndef __CONDITIONAL_NODE_H
#define __CONDITIONAL_NODE_H

class ConditionalNode : public ASTNode {
public:
  ConditionalNode();
  void Analyse( Scope* );
  void AddExpression( ASTNode* );
  void AddIfBlock( BlockNode* );
  void AddElseBlock( BlockNode* );
  ASTNode *Expression() { return expression; }
  BlockNode *IfBlock() { return ifBlock; }
  BlockNode *ElseBlock() { return elseBlock; }
  void GenerateCode(AssemblyBlock*) const;
  std::string Print() const { return "Conditional"; }
private:
  ASTNode *expression;
  BlockNode *elseBlock, *ifBlock;
};

#endif
