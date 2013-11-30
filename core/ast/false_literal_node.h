#ifndef __FALSE_LITERAL_NODE
#define __FALSE_LITERAL_NODE

class FalseLiteralNode : public ASTNode
{
public:
	FalseLiteralNode() {};
	void Analyse(Scope*);
	void GenerateCode(AssemblyBlock*) const;
	void PushOntoStack(AssemblyBlock*) const;
	std::string Print() const { return "FalseLiteral"; }
};

#endif
