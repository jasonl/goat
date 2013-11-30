#ifndef __CONSTANT_ASSIGNMENT_NODE_H
#define __CONSTANT_ASSIGNMENT_NODE_H

class ConstantAssignmentNode : public ASTNode {
public:
 ConstantAssignmentNode(const std::string &_lValue) : lValue(_lValue) {};
  void Analyse( Scope* );
  void SetRValue( ASTNode* );
  const std::string& VariableName() const { return lValue; }
  void GenerateCode(AssemblyBlock*) const;
  std::string Print() const { return "ConstantAssignment: " + lValue; }
  bool IsRelocatedToGlobalObject() const { return true; }
 private:
  const std::string lValue;
};

#endif
