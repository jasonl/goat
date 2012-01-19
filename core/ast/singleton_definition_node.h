#ifndef __SINGLETON_DEFINITION_NODE_H
#define __SINGLETON_DEFINITION_NODE_H

class SingletonDefinitionNode : public ASTNode
{
   public:
    SingletonDefinitionNode(const std::string &_name) : name(_name), lastVarPosition(0) {};
	AssemblyBlock *GenerateCode();
	AssemblyBlock *GetAuxiliaryCode();
	void Analyse(Scope*);

	void AddInstanceVariable(const std::string&);
	int InstanceVariablePosition(const std::string&) const;
	std::string PayloadLabelName() const { return "__" + name + "_ivars"; }

	std::string Print() const { return "SingletonDefinition: " + name; }

#ifdef GOATTEST
	std::string Name() const { return name; }
#endif

  private:
	const std::string name;
	ClassVarMap classVars;
	int lastVarPosition;
};

#endif
