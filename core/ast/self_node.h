class SelfNode : public ASTNode {
public:
	SelfNode() {};
	void Analyse( Scope * );
	void GenerateCode(AssemblyBlock*) const;
	void PushOntoStack(AssemblyBlock*) const;
	std::string Print() const { return "Self"; }
};
