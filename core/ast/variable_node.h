#ifndef __VARIABLE_NODE_H
#define __VARIABLE_NODE_H

class AssignmentTargetNode;

class VariableNode : public AssignmentTargetNode
{
  public:
    VariableNode(const std::string &_name) : name(_name) {};
	void Analyse(Scope*);
	void GenerateCode(AssemblyBlock*) const;
	void GenerateAssignmentCode(AssemblyBlock*) const;
	void PushOntoStack(AssemblyBlock*) const;
	std::string Name() const { return name; }
	std::string Print() const { return "Variable: " + name; }
  private:
	const std::string name;
};

#endif
