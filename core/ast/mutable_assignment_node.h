#ifndef __MUTABLE_ASSIGNMENT_NODE_H
#define __MUTABLE_ASSIGNMENT_NODE_H

class MutableAssignmentNode : public ASTNode {
 public:
 MutableAssignmentNode(const std::string &_lValue) : ASTNode(MutableAssignment), lValue(_lValue) {};
  void Analyse( Scope* );
  void SetRValue( ASTNode* );
  AssemblyBlock *GenerateCode() const;
 private:
  const std::string lValue;
};

#endif
