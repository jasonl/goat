#include <cstdlib>
#include "../goat.h"
#include "../ast_node.h"

// Generates the code to put the integer object into EAX/ECX/EDX.

int32_t IntegerLiteralNode::Value() const
{
	return atol(contents.c_str());
}

void IntegerLiteralNode::GenerateCode(AssemblyBlock* a) const 
{
	a->mov(eax, Dword(Value()));
	a->mov(ecx, Dword(goatHash("Integer")));
	a->mov(edx, *DispatchOperandFor("Integer", scope->GetSourceFile()));
	a->CommentLastInstruction("Move Integer " + contents + " into eax/ecx/edx");
}

// Generates the assembly to push the integer object onto the stack
// for a function call.
void IntegerLiteralNode::PushOntoStack(AssemblyBlock* a) const
{
	a->push(Dword(goatHash("Integer")));
	a->push(*DispatchOperandFor("Integer", scope->GetSourceFile()));
	a->push(Dword(Value()));
	a->CommentLastInstruction("Push Integer " + contents + " onto stack");
}
