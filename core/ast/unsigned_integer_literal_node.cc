#include <cstdlib>
#include "../goat.h"
#include "../ast_node.h"

// Generates the code to put the integer object into EAX/ECX/EDX.

uint32_t UnsignedIntegerLiteralNode::Value() const
{
	return strtol(contents.c_str(), NULL, 16);
}

AssemblyBlock *UnsignedIntegerLiteralNode::GenerateCode() const
{
	AssemblyBlock *a = new AssemblyBlock;

	a->mov(eax, Dword(Value()));
	a->mov(ecx, Dword(goatHash("UnsignedInteger")));
	a->mov(edx, *DispatchOperandFor("UnsignedInteger", scope->GetSourceFile()));

	a->CommentLastInstruction("Move UnsignedInteger " + contents + " into eax/ecx/edx");

	return a;
}

// Generates the assembly to push the integer object onto the stack
// for a function call.
AssemblyBlock *UnsignedIntegerLiteralNode::PushOntoStack() const
{
	AssemblyBlock *a = new AssemblyBlock;

	a->push(Dword(goatHash("UnsignedInteger")));
	a->push(*DispatchOperandFor("UnsignedInteger", scope->GetSourceFile()));
	a->push(Dword(Value()));

	a->CommentLastInstruction("Push UnsignedInteger " + contents + " onto stack");

	return a;
}
