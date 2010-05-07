#ifndef __AST_INTEGER_LITERAL_NODE_H
#define __AST_INTEGER_LITERAL_NODE_H

class ASTIntegerLiteralNode : public ASTNode {
public:
  ASTIntegerLiteralNode( std::string );
  void Analyse( Scope * );
};

#endif
