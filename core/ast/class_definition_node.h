#ifndef __CLASS_DEFINITION_NODE_H
#define __CLASS_DEFINITION_NODE_H

typedef std::map<std::string,int> ClassVarMap;

class ClassDefinitionNode : public ASTNode {
public:
 ClassDefinitionNode( const std::string &_name ) : name(_name), lastVarPosition(0) {};
  AssemblyBlock *GenerateCode();
  AssemblyBlock *GetAuxiliaryCode();
  void Analyse( Scope* );

  void AddClassVariable(const std::string&);
  int ClassVariablePosition(const std::string&) const;

  void RegisterMethod(const std::string&);
  void RegisterClassMethod(const std::string&);

  bool HasMethod(const std::string&);
  bool HasClassMethod(const std::string&);

  std::string Print() const { return "ClassDefinition: " + name; }

#ifdef GOATTEST
  std::string Name() const { return name; }
#endif

 private:
  const std::string name;
  ClassVarMap classVars;
  int lastVarPosition;
  std::set<std::string> methods;
  std::set<std::string> classMethods;
};

#endif
