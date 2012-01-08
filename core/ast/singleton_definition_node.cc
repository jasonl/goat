#include "../ast_node.h"

void SingletonDefinitionNode::Analyse(Scope *_scope)
{
	scope = _scope;
	return;
}

AssemblyBlock *SingletonDefinitionNode::GenerateCode()
{
	return new AssemblyBlock;
}

AssemblyBlock *SingletonDefinitionNode::GetAuxiliaryCode()
{
	return new AssemblyBlock;
}

void SingletonDefinitionNode::AddInstanceVariable(const std::string& var_name)
{
	return;
}
