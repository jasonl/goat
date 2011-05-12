#ifndef __INTEGER_LITERAL_NODE_H
#define __INTEGER_LITERAL_NODE_H

class IntegerLiteralNode : public ASTNode {
 public:
 IntegerLiteralNode( const std::string &_contents ) : ASTNode(IntegerLiteral), contents(_contents) {};
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
#ifdef GOATTEST
  std::string Contents() const { return contents; }
#endif
 private:
  const std::string contents;
};

#endif
