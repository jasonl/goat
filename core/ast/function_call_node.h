#ifndef __FUNCTION_CALL_NODE
#define __FUNCTION_CALL_NODE

class FunctionCallNode : public ASTNode {
 public:
 FunctionCallNode(const std::string &_name) : ASTNode(FunctionCall), name(_name) {};
  ASTNode *Receiver() { return firstChild; }
  void AddReceiver( ASTNode* );
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();

#ifdef GOATTEST
  std::string Name() const { return name; }
#endif

 private:
  const std::string name;
};

#endif
