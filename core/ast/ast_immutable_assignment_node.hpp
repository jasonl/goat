#ifndef __AST_IMMUTABLE_ASSIGNMENT_NODE_H
#define __AST_IMMUTABLE_ASSINGMENT_NODE_H

class ASTImmutableAssignmentNode : public ASTNode {
public:
  ASTImmutableAssignmentNode( TokenIterator& );
  void Analyse( Scope* );
  void SetRValue( ASTNode* );
  ASTIterator ChildNodes();
  AssemblyBlock *GenerateCode();
private:
  ASTNode *rValue;
};

#endif
