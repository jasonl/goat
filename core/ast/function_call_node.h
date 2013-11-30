#ifndef __FUNCTION_CALL_NODE
#define __FUNCTION_CALL_NODE

class FunctionCallNode : public ASTNode {
 public:
 FunctionCallNode(const std::string &_name) : name(_name) {};
  ASTNode *Receiver() const { return firstChild; }
  void AddReceiver( ASTNode* );
  void Analyse( Scope* );
  void GenerateCode(AssemblyBlock*) const;
  void PushOntoStack(AssemblyBlock*) const;
  std::string Print() const { return "FunctionCall: " + name; }

#ifdef GOATTEST
  std::string Name() const { return name; }
#endif

 private:
  enum FC_TYPE {FunctionObjectCall, ClassMethodCall, MethodCall } type;
  const std::string name;

  void GenerateClassMethodCall(AssemblyBlock*) const;
  void GenerateFunctionObjectCall(AssemblyBlock*) const;
  void GenerateMethodCall(AssemblyBlock*) const;
  int PushParametersOntoStack(AssemblyBlock*, bool) const;
};

#endif
