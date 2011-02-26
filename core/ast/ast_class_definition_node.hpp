#ifndef __AST_CLASS_DEFINITION_NODE_H
#define __AST_CLASS_DEFINITION_NODE_H

class ASTClassDefinitionNode : public ASTNode {
public:
  ASTClassDefinitionNode( Token& );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *GetAuxiliaryCode();
  void Analyse( Scope* );
};

#endif
