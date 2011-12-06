#ifndef __PARAMETER_NODE_H
#define __PARAMETER_NODE_H

class ParameterNode : public ASTNode {
public:
	ParameterNode() {};
  void Analyse( Scope* );
  AssemblyBlock *PushOntoStack();
  std::string Print() const { return "Parameter"; }
};

#endif
