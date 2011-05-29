#ifndef __CLASS_DEFINITION_NODE_H
#define __CLASS_DEFINITION_NODE_H

#include <map>

typedef std::map<std::string,int> ClassVarMap;

class ClassDefinitionNode : public ASTNode {
public:
 ClassDefinitionNode( const std::string &_name ) : ASTNode(ClassDefinition), name(_name), lastVarPosition(0) {};
  AssemblyBlock *GenerateCode();
  AssemblyBlock *GetAuxiliaryCode();
  void Analyse( Scope* );

  void AddClassVariable(const std::string&);
  int ClassVariablePosition(const std::string&) const;

#ifdef GOATTEST
  std::string Name() const { return name; }
#endif

 private:
  const std::string name;
  ClassVarMap classVars;
  int lastVarPosition;
};

#endif
