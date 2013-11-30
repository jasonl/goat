#define OBJECT_SIZE 12

// Byte offsets of the object components from the base address
#define PAYLOAD_OFFSET 0
#define DISPATCH_OFFSET 4
#define TYPE_OFFSET 8

class ClassDefinitionNode;
class SingletonDefinitionNode;
class AssignmentTargetNode;

class ClassVariableNode : public AssignmentTargetNode
{
public:
	ClassVariableNode (std::string _name) : name(_name) {};
	void Analyse(Scope*);
	void GenerateCode(AssemblyBlock*) const;
	void GenerateAssignmentCode(AssemblyBlock*) const;
	void PushOntoStack(AssemblyBlock*) const;

	int32_t TypeHashOffset() const;
	int32_t DispatchOffset() const;
	int32_t PayloadOffset() const;
	int32_t InstanceVariablePosition() const;

	ClassDefinitionNode* MutableEnclosingClassDefinition();
	const ClassDefinitionNode* EnclosingClassDefinition() const;
	SingletonDefinitionNode* MutableEnclosingSingletonDefinition();
	const SingletonDefinitionNode* EnclosingSingletonDefinition() const;

	std::string Print() const { return "ClassVariable: " + name; }
	std::string Name() const { return name; }

private:
	const std::string name;
	enum {CLASS_IVAR, SINGLETON_IVAR} type;
};
