#ifndef __PARAMETER_DEF_NODE
#define __PARAMETER_DEF_NODE

class ParameterDefNode : public ASTNode {
public:
  ParameterDefNode( TokenIterator& );
  void Analyse( Scope* );
};

#endif
