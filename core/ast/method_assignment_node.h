#ifndef __METHOD_ASSIGNMENT_NODE_H
#define __METHOD_ASSIGNMENT_NODE_H

#include "function_def_node.h"

class MethodAssignmentNode : public ASTNode {
  public:
    MethodAssignmentNode(const std::string &_lValue) : lValue(_lValue){};
	void Analyse(Scope*);
	void SetRValue(FunctionDefNode*);
	const std::string& Name() const { return lValue; }
	int ParameterCount() const { return functionNode->ParameterCount(); }
	AssemblyBlock *GenerateCode() const;
	std::string Print() const { return "MethodAssignment: " + lValue; }

  private:
	const std::string lValue;
	FunctionDefNode *functionNode;
};

#endif
