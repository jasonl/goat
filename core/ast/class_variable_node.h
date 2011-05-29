#define OBJECT_SIZE 12

// Byte offsets of the object components from the base address
#define PAYLOAD_OFFSET 0
#define DISPATCH_OFFSET 4
#define TYPE_OFFSET 8

class ClassDefinitionNode;

class ClassVariableNode : public ASTNode
{
  public:
    ClassVariableNode(std::string _name) : ASTNode(ClassVariable), name(_name) {};
	void Analyse(Scope*);
	AssemblyBlock *GenerateCode();
	AssemblyBlock *PushOntoStack();
	int32_t TypeHashOffset();
	int32_t DispatchOffset();
	int32_t PayloadOffset();
	ClassDefinitionNode *EnclosingClassDefinition();

#ifdef GOATTEST
	std::string Name() const { return name; }
#endif
 private:
   const std::string name;
};
