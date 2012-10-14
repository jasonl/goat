#ifndef __CLASS_DEFINITION_NODE_H
#define __CLASS_DEFINITION_NODE_H

class MethodAssignmentNode;
class ClassMethodAssignmentNode;

typedef std::map<std::string,int> ClassVarMap;

typedef std::list<MethodAssignmentNode*>::iterator MethodIterator;
typedef std::list<ClassMethodAssignmentNode*>::iterator ClassMethodIterator;

class ClassDefinitionNode : public ASTNode {
public:
 ClassDefinitionNode( const std::string &_name ) : name(_name), lastVarPosition(0) {};
  AssemblyBlock *GenerateCode();
  AssemblyBlock *GetAuxiliaryCode();
  void Analyse( Scope* );

  void AddClassVariable(const std::string&);
  int ClassVariablePosition(const std::string&) const;

  void RegisterMethod(const std::string&, int);
  void RegisterClassMethod(const std::string&, int);

  bool HasMethod(const std::string&);
  bool HasClassMethod(const std::string&);

  int ParamCountForClassMethod(const std::string&);
  int ParamCountForMethod(const std::string&);

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
  std::list<MethodAssignmentNode*> methodNodes;
  std::list<ClassMethodAssignmentNode*> classMethodNodes;
  std::map<std::string, int> methods;
  std::map<std::string, int> classMethods;
};

#endif
