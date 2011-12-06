#ifndef __CLASS_LITERAL_NODE
#define __CLASS_LITERAL_NODE

class ClassLiteralNode : public ASTNode {
 public:
  ClassLiteralNode(const std::string _name) : ASTNode(), name(_name) {};
  const std::string Name() { return name; }
  std::string Print() const { return "ClassLiteral: " + name; }
 private:
  const std::string name;
};

#endif
