#ifndef __MUTABLE_ASSIGNMENT_NODE_H
#define __MUTABLE_ASSIGNMENT_NODE_H

class MutableAssignmentNode : public ASTNode {
public:
  MutableAssignmentNode( TokenIterator& );
  void Analyse( Scope* );
  void SetRValue( ASTNode* );
  AssemblyBlock *GenerateCode();
};

#endif
