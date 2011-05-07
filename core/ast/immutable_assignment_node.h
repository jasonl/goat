#ifndef __IMMUTABLE_ASSIGNMENT_NODE_H
#define __IMMUTABLE_ASSINGMENT_NODE_H

class ImmutableAssignmentNode : public ASTNode {
public:
 ImmutableAssignmentNode(const std::string &_lValue) : ASTNode(ImmutableAssignment), lValue(_lValue) {};
  void Analyse( Scope* );
  void SetRValue( ASTNode* );
  const std::string& VariableName() const { return lValue; }
  AssemblyBlock *GenerateCode() const;
 private:
  const std::string lValue;
};

#endif
