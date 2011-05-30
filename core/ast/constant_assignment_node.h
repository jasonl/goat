#ifndef __CONSTANT_ASSIGNMENT_NODE_H
#define __CONSTANT_ASSIGNMENT_NODE_H

class ConstantAssignmentNode : public ASTNode {
public:
 ConstantAssignmentNode(const std::string &_lValue) : ASTNode(ConstantAssignment), lValue(_lValue) {};
  void Analyse( Scope* );
  void SetRValue( ASTNode* );
  const std::string& VariableName() const { return lValue; }
  AssemblyBlock *GenerateCode() const;
 private:
  const std::string lValue;
};

#endif
