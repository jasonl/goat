class AssignmentTargetNode : public ASTNode
{
  public:
    AssignmentTargetNode() {};
	virtual void Analyse(Scope*) = 0;
	virtual AssemblyBlock* GenerateCode() const = 0;
	virtual AssemblyBlock* PushOntoStack() const = 0;
	virtual AssemblyBlock* GenerateAssignmentCode() const = 0;
	virtual std::string Name() const = 0;
};
