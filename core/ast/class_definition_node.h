#ifndef __CLASS_DEFINITION_NODE_H
#define __CLASS_DEFINITION_NODE_H

class MethodAssignmentNode;
class ClassMethodAssignmentNode;

typedef std::map<std::string,int> ClassVarMap;

typedef std::list<MethodAssignmentNode*> MethodNodeList;
typedef std::list<ClassMethodAssignmentNode*> ClassMethodList;

class ClassDefinitionNode : public ASTNode {
public:
 ClassDefinitionNode( const std::string &_name ) : name(_name), lastVarPosition(0) {};
  void GenerateCode(AssemblyBlock*) const;
  void GetAuxiliaryCode(AssemblyBlock*) const;
  void GenerateInitializer(AssemblyBlock*) const;
  void Analyse(Scope*);

  void AddClassVariable(const std::string&);
  int ClassVariablePosition(const std::string&) const;

  void RegisterMethod(const std::string&, int);
  void RegisterClassMethod(const std::string&, int);

  bool HasMethod(const std::string&) const;
  bool HasClassMethod(const std::string&) const;

  int ParamCountForClassMethod(const std::string&) const;
  int ParamCountForMethod(const std::string&) const;

  void AppendMethod(MethodAssignmentNode*);
  void AppendClassMethod(ClassMethodAssignmentNode*);

  std::string Print() const { return "ClassDefinition: " + name; }

#ifdef GOATTEST
  std::string Name() const { return name; }
#endif

 private:
  const std::string name;
  ClassVarMap classVars;
  int lastVarPosition;
  MethodNodeList methodNodes;
  ClassMethodList classMethodNodes;
  std::map<std::string, int> methods;
  std::map<std::string, int> classMethods;
};

#endif
