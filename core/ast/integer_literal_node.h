#ifndef __INTEGER_LITERAL_NODE_H
#define __INTEGER_LITERAL_NODE_H

class IntegerLiteralNode : public ASTNode {
 public:
  IntegerLiteralNode( TokenIterator& );
  void Analyse( Scope * );
  AssemblyBlock *GenerateCode();
  AssemblyBlock *PushOntoStack();
};

#endif
