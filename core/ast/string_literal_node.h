#ifndef __STRING_LITERAL_NODE_H
#define __STRING_LITERAL_NODE_H

class StringLiteralNode : public ASTNode {
 public:
  StringLiteralNode( Token& );
  void Analyse( Scope * );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
 private:
  std::string strLabelName;
};

#endif
