#ifndef __AST_MUTABLE_ASSIGNMENT_NODE_H
#define __AST_MUTABLE_ASSIGNMENT_NODE_H

class ASTMutableAssignmentNode : public ASTNode {
public:
  ASTMutableAssignmentNode( TokenIterator& );
  void Analyse( Scope* );
  void SetRValue( ASTNode* );
private:
  ASTNode *rValue;
};

#endif
