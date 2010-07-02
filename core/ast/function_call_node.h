#ifndef __FUNCTION_CALL_NODE
#define __FUNCTION_CALL_NODE

class FunctionCallNode : public ASTNode {
public:
  FunctionCallNode( TokenIterator& );
  FunctionCallNode( Token *_token ); // For the transform from VariableNode
  ASTNode *Receiver() { return receiver; }
  void AddReceiver( ASTNode* );
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
private:
  ASTNode *receiver;
};

#endif
