#ifndef __FALSE_LITERAL_NODE
#define __FALSE_LITERAL_NODE

class FalseLiteralNode : public ASTNode
{
  public:
	FalseLiteralNode() {};
	void Analyse(Scope*);
	AssemblyBlock *GenerateCode();
	AssemblyBlock *PushOntoStack();
	std::string Print() const { return "FalseLiteral"; }
};

#endif
