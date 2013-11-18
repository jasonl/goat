class SelfNode : public ASTNode {
public:
	SelfNode() {};
	void Analyse( Scope * );
	AssemblyBlock *GenerateCode() const;
	AssemblyBlock *PushOntoStack() const;
	std::string Print() const { return "Self"; }
};
