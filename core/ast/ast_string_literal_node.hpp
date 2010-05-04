#ifndef __AST_STRING_LITERAL_NODE_H
#define __AST_STRING_LITERAL_NODE_H

class ASTStringLiteralNode : public ASTNode {
public:
  ASTStringLiteralNode( struct _Token * );
  void Analyse( Scope * );
};

#endif
