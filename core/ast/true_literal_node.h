#ifndef __TRUE_LITERAL_NODE
#define __TRUE_LITERAL_NODE

class TrueLiteralNode : public ASTNode {
public:
	TrueLiteralNode() {};
	void Analyse( Scope* );
	void GenerateCode(AssemblyBlock*) const;
	void PushOntoStack(AssemblyBlock*) const;
	std::string Print() const { return "TrueLiteral"; }
};

#endif
