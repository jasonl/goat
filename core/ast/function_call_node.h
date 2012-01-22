#ifndef __FUNCTION_CALL_NODE
#define __FUNCTION_CALL_NODE

class FunctionCallNode : public ASTNode {
 public:
 FunctionCallNode(const std::string &_name) : name(_name) {};
  ASTNode *Receiver() { return firstChild; }
  void AddReceiver( ASTNode* );
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
  std::string Print() const { return "FunctionCall: " + name; }

#ifdef GOATTEST
  std::string Name() const { return name; }
#endif

 private:
  enum FC_TYPE {FunctionObjectCall, ClassMethodCall, MethodCall } type;
  const std::string name;

  void GenerateClassMethodCall(AssemblyBlock*);
  void GenerateFunctionObjectCall(AssemblyBlock*);
  void GenerateMethodCall(AssemblyBlock*);
  int PushParametersOntoStack(AssemblyBlock*, bool);
};

#endif
