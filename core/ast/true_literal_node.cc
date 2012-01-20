#include "../goat.h"
#include "../ast_node.h"

void TrueLiteralNode::Analyse(Scope *_scope)
{
	scope = _scope;
}

AssemblyBlock *TrueLiteralNode::GenerateCode()
{
	AssemblyBlock *a = new AssemblyBlock();

	a->mov(eax, Dword(1));
	a->mov(ecx, Dword(goatHash("Boolean")));
	a->mov(edx, *DispatchOperandFor("Boolean", scope->GetSourceFile()));

	a->CommentLastInstruction("Move true literal into eax/ecx/edx");

	return a;
}

AssemblyBlock *TrueLiteralNode::PushOntoStack()
{
	AssemblyBlock *a = new AssemblyBlock();

	a->push(Dword(goatHash("Boolean")));
	a->push(*DispatchOperandFor("Boolean", scope->GetSourceFile()));
	a->push(Dword(1));

	a->CommentLastInstruction("Push true literal onto stack");

	return a;
}
