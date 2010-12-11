#ifndef __AST_CLASS_DEFINITION_NODE_H
#define __AST_CLASS_DEFINITION_NODE_H

class ASTClassDefinitionNode : public ASTNode {
public:
  ASTClassDefinitionNode( TokenIterator& );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *GetAuxiliaryCode();
  void Analyse( Scope* );
};

#endif
