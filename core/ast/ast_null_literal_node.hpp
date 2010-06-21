#ifndef __AST_NULL_LITERAL_NODE
#define __AST_NULL_LITERAL_NODE

class ASTNullLiteralNode : public ASTNode {
public:
  ASTNullLiteralNode();
  void Analyse( Scope* );
  AssemblyBlock *GenerateCode();
};

#endif
