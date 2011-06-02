#include "../goat.h"
#include "../ast_node.h"

void ClassVariableNode::Analyse(Scope *_scope)
{
	scope = _scope;
	ClassDefinitionNode *cd = MutableEnclosingClassDefinition();

	if(cd == NULL) {
		goatError(0, "Class Variable referenced outside Class Definition");
	    return;
	}

	cd->AddClassVariable(name);
}

AssemblyBlock *ClassVariableNode::GenerateCode()
{
	std::cout << "Blah";

	AssemblyBlock *a = new AssemblyBlock();

	a->mov(ebx, scope->GeneratePayloadOperand("self"));
	a->mov(eax, _[ebx + PayloadOffset()]);
	a->mov(edx, _[ebx + DispatchOffset()]);
	a->mov(ecx, _[ebx + TypeHashOffset()]);

	return a;
}

AssemblyBlock *ClassVariableNode::GenerateAssignmentCode()
{
	AssemblyBlock *a = new AssemblyBlock();

	a->mov(ebx, scope->GeneratePayloadOperand("self"));
	a->mov(_[ebx + PayloadOffset()], eax);
	a->mov(_[ebx + DispatchOffset()], edx);
	a->mov(_[ebx + TypeHashOffset()], ecx);

	return a;
}

AssemblyBlock *ClassVariableNode::PushOntoStack()
{
	AssemblyBlock *a = new AssemblyBlock;

	a->mov(ebx, scope->GeneratePayloadOperand("self"));
	a->push( Dword(_[ebx + TypeHashOffset()]));
	a->push( Dword(_[ebx + DispatchOffset()]));
	a->push( Dword(_[ebx + PayloadOffset()]));

	return a;
}

int32_t ClassVariableNode::TypeHashOffset() const
{
	const ClassDefinitionNode *cn = EnclosingClassDefinition();

	return cn->ClassVariablePosition(name) * OBJECT_SIZE + TYPE_OFFSET;
}

int32_t ClassVariableNode::PayloadOffset() const
{
	const ClassDefinitionNode *cn = EnclosingClassDefinition();

	return cn->ClassVariablePosition(name) * OBJECT_SIZE + PAYLOAD_OFFSET;
}

int32_t ClassVariableNode::DispatchOffset() const
{
	const ClassDefinitionNode *cn = EnclosingClassDefinition();

	return cn->ClassVariablePosition(name) * OBJECT_SIZE + DISPATCH_OFFSET;
}

ClassDefinitionNode* ClassVariableNode::MutableEnclosingClassDefinition()
{
	ASTNode *cd = MutableFindEnclosingNode(ClassDefinition);

	if(cd == NULL) {
		return NULL; // Won't be reached
	} else {
		return dynamic_cast<ClassDefinitionNode*>(cd);
	}
}

const ClassDefinitionNode* ClassVariableNode::EnclosingClassDefinition() const
{
	const ASTNode *cd = FindEnclosingNode(ClassDefinition);

	if(cd == NULL) {
		return NULL; // Won't be reached
	} else {
		return dynamic_cast<const ClassDefinitionNode*>(cd);
	}
}
