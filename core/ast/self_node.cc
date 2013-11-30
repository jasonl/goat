#include "../goat.h"
#include "../ast_node.h"

void SelfNode::Analyse( Scope *_scope ) {
  scope = _scope;
}

void SelfNode::GenerateCode(AssemblyBlock* a) const
{
	a->mov(eax, scope->GeneratePayloadOperand("self"));
	a->mov(ecx, scope->GenerateTypeHashOperand("self"));
	a->mov(edx, scope->GenerateDispatchOperand("self"));
	a->CommentLastInstruction("Move self into eax/ecx/edx");
}

void SelfNode::PushOntoStack(AssemblyBlock* a) const
{
	a->push(Dword(scope->GenerateTypeHashOperand("self")));
	a->push(Dword(scope->GenerateDispatchOperand("self")));
	a->push(Dword(scope->GeneratePayloadOperand("self")));
	a->CommentLastInstruction("Push self onto stack");

}
