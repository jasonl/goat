#ifndef __INTEGER_LITERAL_NODE_H
#define __INTEGER_LITERAL_NODE_H

class IntegerLiteralNode : public ASTNode {
 public:
 IntegerLiteralNode( const std::string &_contents ) : ASTNode(IntegerLiteral), contents(_contents) {};
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
 private:
  const std::string contents;
};

#endif
