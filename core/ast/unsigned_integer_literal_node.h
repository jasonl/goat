#ifndef __UNSIGNED_INTEGER_LITERAL_NODE_H
#define __UNSIGNED_INTEGER_LITERAL_NODE_H

class UnsignedIntegerLiteralNode : public ASTNode
{
 public:
 UnsignedIntegerLiteralNode(const std::string &_contents) : contents(_contents) {};
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
  std::string Print() const { return "UnsignedIntegerLiteral: " + contents; }
  uint32_t Value() const;
#ifdef GOATTEST
  std::string Contents() const { return contents; }
#endif
 private:
  const std::string contents;
};

#endif
