#ifndef __METHOD_ASSIGNMENT_NODE_H
#define __METHOD_ASSIGNMENT_NODE_H

class MethodAssignmentNode : public ASTNode {
public:
 MethodAssignmentNode(const std::string &_lValue) : lValue(_lValue) {};
  void Analyse( Scope* );
  void SetRValue( ASTNode* );
  const std::string& Name() const { return lValue; }
  AssemblyBlock *GenerateCode() const;
  std::string Print() const { return "MethodAssignment: " + lValue; }
 private:
  const std::string lValue;
};

#endif
