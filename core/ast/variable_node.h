#ifndef __VARIABLE_NODE_H
#define __VARIABLE_NODE_H

class VariableNode : public ASTNode {
public:
  VariableNode( const std::string &_name ) : ASTNode(Variable), name(_name) {};
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
 private:
  const std::string name;
};

#endif
