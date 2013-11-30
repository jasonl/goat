#include "../goat.h"
#include "../ast_node.h"

void ClassVariableNode::Analyse(Scope *_scope)
{
	scope = _scope;
	ClassDefinitionNode *cd = MutableEnclosingClassDefinition();

	if (cd) {
		cd->AddClassVariable(name);
		type = CLASS_IVAR;
	    return;
	}

	SingletonDefinitionNode *sd = MutableEnclosingSingletonDefinition();

	if (sd) {
		sd->AddInstanceVariable(name);
		type = SINGLETON_IVAR;
		return;
	}

	goatError(0, "Class Variable referenced outside Class Definition");
}

void ClassVariableNode::GenerateCode(AssemblyBlock* a) const
{
	if (type == CLASS_IVAR) 
	{
		a->mov(ebx, scope->GeneratePayloadOperand("self"));
	} else {
		const SingletonDefinitionNode* sd = EnclosingSingletonDefinition();
		a->mov(ebx, *new Operand(sd->PayloadLabelName()));
	}

	a->mov(eax, _[ebx + PayloadOffset()]);
	a->mov(edx, _[ebx + DispatchOffset()]);
	a->mov(ecx, _[ebx + TypeHashOffset()]);
}

void ClassVariableNode::GenerateAssignmentCode(AssemblyBlock* a) const
{
	if (type == CLASS_IVAR) {
		a->mov(ebx, scope->GeneratePayloadOperand("self"));
	} else {
		const SingletonDefinitionNode* sd = EnclosingSingletonDefinition();
		a->mov(ebx, *new Operand(sd->PayloadLabelName()));
	}

	a->mov(_[ebx + PayloadOffset()], eax);
	a->mov(_[ebx + DispatchOffset()], edx);
	a->mov(_[ebx + TypeHashOffset()], ecx);
}

void ClassVariableNode::PushOntoStack(AssemblyBlock* a) const
{
	if (type == CLASS_IVAR) {
		a->mov(ebx, scope->GeneratePayloadOperand("self"));
	} else {
		const SingletonDefinitionNode* sd = EnclosingSingletonDefinition();
		a->mov(ebx, *new Operand(sd->PayloadLabelName()));
	}

	a->push( Dword(_[ebx + TypeHashOffset()]));
	a->push( Dword(_[ebx + DispatchOffset()]));
	a->push( Dword(_[ebx + PayloadOffset()]));
}

int32_t ClassVariableNode::TypeHashOffset() const
{
	return InstanceVariablePosition() * OBJECT_SIZE + TYPE_OFFSET;
}

int32_t ClassVariableNode::PayloadOffset() const
{
	return InstanceVariablePosition() * OBJECT_SIZE + PAYLOAD_OFFSET;
}

int32_t ClassVariableNode::DispatchOffset() const
{
	return InstanceVariablePosition() * OBJECT_SIZE + DISPATCH_OFFSET;
}

int32_t ClassVariableNode::InstanceVariablePosition() const
{
	if (type == CLASS_IVAR) {
		return EnclosingClassDefinition()->ClassVariablePosition(name);
	} else {
		return EnclosingSingletonDefinition()->InstanceVariablePosition(name);
	}
}

ClassDefinitionNode* ClassVariableNode::MutableEnclosingClassDefinition()
{
	ASTNode *cd = MutableFindEnclosingNode(typeid(ClassDefinitionNode).name());

	if(cd == NULL) {
		return NULL; // Won't be reached
	} else {
		return dynamic_cast<ClassDefinitionNode*>(cd);
	}
}

const ClassDefinitionNode* ClassVariableNode::EnclosingClassDefinition() const
{
	const ASTNode *cd = FindEnclosingNode(typeid(ClassDefinitionNode).name());

	if(cd == NULL) {
		return NULL; // Won't be reached
	} else {
		return dynamic_cast<const ClassDefinitionNode*>(cd);
	}
}

SingletonDefinitionNode* ClassVariableNode::MutableEnclosingSingletonDefinition()
{
	ASTNode *sd = MutableFindEnclosingNode(typeid(SingletonDefinitionNode).name());

	if (sd)
		return dynamic_cast<SingletonDefinitionNode*>(sd);

	return NULL; // Won't be reached
}

const SingletonDefinitionNode* ClassVariableNode::EnclosingSingletonDefinition() const
{
	const ASTNode *sd = FindEnclosingNode(typeid(SingletonDefinitionNode).name());

	if (sd)
		return dynamic_cast<const SingletonDefinitionNode*>(sd);

	return NULL; // Won't be reached
}
