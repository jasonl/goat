#ifndef __CLASS_LITERAL_NODE
#define __CLASS_LITERAL_NODE

class ClassLiteralNode : public ASTNode {
 public:
  ClassLiteralNode(const std::string _name) : ASTNode(ClassLiteral), name(_name) {};
  const std::string Name() { return name; }
 private:
  const std::string name;
};

#endif
