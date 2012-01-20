#include "../goat.h"
#include "../ast_node.h"

void FalseLiteralNode::Analyse( Scope *_scope )
{
  scope = _scope;
}

AssemblyBlock *FalseLiteralNode::GenerateCode()
{
	AssemblyBlock *a = new AssemblyBlock();

	a->mov(eax, Dword(0));
	a->mov(ecx, Dword(goatHash("Boolean")));
	a->mov(edx, *DispatchOperandFor("Boolean", scope->GetSourceFile()));

	a->CommentLastInstruction("Move false literal into eax/ecx/edx");

	return a;
}

AssemblyBlock *FalseLiteralNode::PushOntoStack()
{
	AssemblyBlock *a = new AssemblyBlock();

	a->push(Dword(goatHash("Boolean")));
	a->push(*DispatchOperandFor("Boolean", scope->GetSourceFile())); //TODO: This needs to reference a label
	a->push(Dword(0));

	a->CommentLastInstruction("Push false literal onto stack");

	return a;
}
