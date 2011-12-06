class SelfNode : public ASTNode {
public:
	SelfNode() {};
	void Analyse( Scope * );
	AssemblyBlock *GenerateCode();
	AssemblyBlock *PushOntoStack();
	std::string Print() const { return "Self"; }
};
