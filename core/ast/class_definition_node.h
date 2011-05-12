#ifndef __CLASS_DEFINITION_NODE_H
#define __CLASS_DEFINITION_NODE_H

class ClassDefinitionNode : public ASTNode {
public:
  ClassDefinitionNode( const std::string &_name ) : ASTNode(ClassDefinition), name(_name) {};
  AssemblyBlock *GenerateCode();
  AssemblyBlock *GetAuxiliaryCode();
  void Analyse( Scope* );

#ifdef GOATTEST
  std::string Name() const { return name; }
#endif

 private:
  const std::string name;
};

#endif
