#ifndef __CLASS_DEFINITION_NODE_H
#define __CLASS_DEFINITION_NODE_H

class ClassDefinitionNode : public ASTNode {
public:
  ClassDefinitionNode( Token& );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *GetAuxiliaryCode();
  void Analyse( Scope* );
};

#endif
