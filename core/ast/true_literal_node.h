#ifndef __TRUE_LITERAL_NODE
#define __TRUE_LITERAL_NODE

class TrueLiteralNode : public ASTNode {
 public:
	TrueLiteralNode() {};
	void Analyse( Scope* );
	AssemblyBlock *GenerateCode();
	AssemblyBlock *PushOntoStack();
	std::string Print() const { return "TrueLiteral"; }
};

#endif
