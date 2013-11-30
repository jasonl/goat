#ifndef __CLASS_METHOD_ASSIGNMENT_NODE_H
#define __CLASS_METHOD_ASSIGNMENT_NODE_H

#include "function_def_node.h"

class ClassMethodAssignmentNode : public ASTNode
{
  public:
    ClassMethodAssignmentNode(const std::string &_lValue) : lValue(_lValue) {};
	void Analyse( Scope* );
	void SetRValue( FunctionDefNode* );
	const std::string& Name() const { return lValue; }
	int ParameterCount() const { return functionNode->ParameterCount(); }
	void GenerateCode(AssemblyBlock*) const;
	std::string Print() const { return "ClassMethodAssignment: " + lValue; }

  private:
	const std::string lValue;
	FunctionDefNode *functionNode;
};

#endif
