#ifndef __FALSE_LITERAL_NODE
#define __FALSE_LITERAL_NODE

class FalseLiteralNode : public ASTNode
{
  public:
	FalseLiteralNode(): ASTNode(ASTNode::FalseLiteral) {};
	void Analyse(Scope*);
	AssemblyBlock *GenerateCode();
	AssemblyBlock *PushOntoStack();
};

#endif
