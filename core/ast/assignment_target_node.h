class AssignmentTargetNode : public ASTNode
{
public:
    AssignmentTargetNode() {};
    virtual void Analyse(Scope*) = 0;
    virtual void GenerateCode(AssemblyBlock*) const = 0;
    virtual void PushOntoStack(AssemblyBlock*) const = 0;
    virtual void GenerateAssignmentCode(AssemblyBlock*) const = 0;
    virtual std::string Name() const = 0;
};
