#ifndef __AST_FUNCTION_CALL_NODE
#define __AST_FUNCTION_CALL_NODE

class ASTFunctionCallNode : public ASTNode {
public:
  ASTFunctionCallNode( TokenIterator& );
  ASTNode *Receiver() { return receiver; }
  void AddReceiver( ASTNode* );
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
private:
  ASTNode *receiver;
};

#endif
