#ifndef __AST_FUNCTION_CALL_NODE
#define __AST_FUNCTION_CALL_NODE

class ASTFunctionCallNode : public ASTNode {
public:
  ASTFunctionCallNode();
  void Analyse( Scope* );
};

#endif
