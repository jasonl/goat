#define OBJECT_SIZE 12

// Byte offsets of the object components from the base address
#define PAYLOAD_OFFSET 0
#define DISPATCH_OFFSET 4
#define TYPE_OFFSET 8

class ClassDefinitionNode;
class AssignmentTargetNode;

class ClassVariableNode : public AssignmentTargetNode
{
  public:
    ClassVariableNode(std::string _name) : AssignmentTargetNode(ClassVariable), name(_name) {};
	void Analyse(Scope*);
	AssemblyBlock *GenerateCode();
	AssemblyBlock *GenerateAssignmentCode();
	AssemblyBlock *PushOntoStack();
	int32_t TypeHashOffset() const;
	int32_t DispatchOffset() const;
	int32_t PayloadOffset() const;
	ClassDefinitionNode* MutableEnclosingClassDefinition();
	const ClassDefinitionNode* EnclosingClassDefinition() const;
	std::string Name() const { return name; }
 private:
   const std::string name;
};
