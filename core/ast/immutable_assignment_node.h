#ifndef __IMMUTABLE_ASSIGNMENT_NODE_H
#define __IMMUTABLE_ASSINGMENT_NODE_H

class ImmutableAssignmentNode : public ASTNode {
public:
  ImmutableAssignmentNode( TokenIterator& );
  void Analyse( Scope* );
  void SetRValue( ASTNode* );
  ASTIterator ChildNodes();
  AssemblyBlock *GenerateCode();
};

#endif
