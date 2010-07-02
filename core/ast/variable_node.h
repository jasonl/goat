#ifndef __VARIABLE_NODE_H
#define __VARIABLE_NODE_H

class VariableNode : public ASTNode {
public:
  VariableNode( TokenIterator& );
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
};

#endif
