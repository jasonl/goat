#ifndef __NULL_LITERAL_NODE
#define __NULL_LITERAL_NODE

class NullLiteralNode : public ASTNode {
public:
	NullLiteralNode() {}
	void Analyse( Scope* );
	AssemblyBlock *GenerateCode();
	AssemblyBlock *PushOntoStack();
	std::string Print() const { return "NullLiteral"; }
};

#endif
