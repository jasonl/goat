#ifndef __FALSE_LITERAL_NODE
#define __FALSE_LITERAL_NODE

class FalseLiteralNode : public ASTNode
{
  public:
	FalseLiteralNode() {};
	void Analyse(Scope*);
	AssemblyBlock *GenerateCode() const;
	AssemblyBlock *PushOntoStack() const;
	std::string Print() const { return "FalseLiteral"; }
};

#endif
