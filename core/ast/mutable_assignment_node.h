#ifndef __MUTABLE_ASSIGNMENT_NODE_H
#define __MUTABLE_ASSIGNMENT_NODE_H

class AssignmentTargetNode;

class MutableAssignmentNode : public ASTNode
{
  public:
	MutableAssignmentNode(AssignmentTargetNode*, ASTNode*);
	void Analyse( Scope* );
	AssemblyBlock *GenerateCode() const;
	std::string VariableName() const { return target->Name(); }
	std::string Print() const { return "MutableAssignment"; }
	bool IsRelocatedToGlobalObject() const { return true; }
  private:
	AssignmentTargetNode *target;
	ASTNode *rValue;
};

#endif
