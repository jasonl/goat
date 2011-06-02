#ifndef __VARIABLE_NODE_H
#define __VARIABLE_NODE_H

class AssignmentTargetNode;

class VariableNode : public AssignmentTargetNode
{
  public:
    VariableNode( const std::string &_name ) : AssignmentTargetNode(Variable), name(_name) {};
	void Analyse( Scope* );
	AssemblyBlock *GenerateCode();
	AssemblyBlock *GenerateAssignmentCode();
	AssemblyBlock *PushOntoStack();
	std::string Name() const { return name; }

 private:
	const std::string name;
};

#endif
