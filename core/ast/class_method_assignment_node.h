#ifndef __CLASS_METHOD_ASSIGNMENT_NODE_H
#define __CLASS_METHOD_ASSIGNMENT_NODE_H

class ClassMethodAssignmentNode : public ASTNode
{
  public:
    ClassMethodAssignmentNode(const std::string &_lValue) : ASTNode(ClassMethodAssignment), lValue(_lValue) {};
	void Analyse( Scope* );
	void SetRValue( ASTNode* );
	const std::string& Name() const { return lValue; }
	AssemblyBlock *GenerateCode() const;
	std::string PrintableIdentifier() { return ": " + lValue; }
  private:
	const std::string lValue;
};

#endif
