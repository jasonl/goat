#ifndef __NULL_LITERAL_NODE
#define __NULL_LITERAL_NODE

class NullLiteralNode : public ASTNode {
public:
	NullLiteralNode() {}
	void Analyse( Scope* );
	void GenerateCode(AssemblyBlock*) const;
	void PushOntoStack(AssemblyBlock*) const;
	std::string Print() const { return "NullLiteral"; }
};

#endif
