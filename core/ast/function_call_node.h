#ifndef __FUNCTION_CALL_NODE
#define __FUNCTION_CALL_NODE

class FunctionCallNode : public ASTNode {
 public:
 FunctionCallNode(const std::string &_name) : ASTNode(FunctionCall), name(_name), receiver(NULL) {};
  ASTNode *Receiver() { return receiver; }
  void AddReceiver( ASTNode* );
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();

#ifdef GOATTEST
  std::string Name() const { return name; }
#endif

 private:
  const std::string name;
  ASTNode *receiver;
};

#endif
