#ifndef __STRING_LITERAL_NODE_H
#define __STRING_LITERAL_NODE_H

class StringLiteralNode : public ASTNode {
 public:
  StringLiteralNode(const std::string &_contents) : contents(_contents) {};
  void Analyse( Scope * );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
  std::string Print() const { return "StringLiteral: \"" + contents + "\""; }

#ifdef GOATTEST
  std::string Contents() const { return contents; }
#endif

 private:
  std::string contents;
  std::string strLabelName;
};

#endif
