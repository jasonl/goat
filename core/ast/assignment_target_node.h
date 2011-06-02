class AssignmentTargetNode : public ASTNode
{
  public:
    AssignmentTargetNode(enum NODE_TYPE _type) : ASTNode(_type) {};
	virtual void Analyse(Scope*) = 0;
	virtual AssemblyBlock* GenerateCode() = 0;
	virtual AssemblyBlock* PushOntoStack() = 0;;
	virtual AssemblyBlock* GenerateAssignmentCode() = 0;
	virtual std::string Name() const = 0;
};
