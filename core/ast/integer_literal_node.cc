#include <cstdlib>
#include "../goat.h"
#include "../ast_node.h"

// Generates the code to put the integer object into EAX/ECX/EDX.

int32_t IntegerLiteralNode::Value() const
{
	return atol(contents.c_str());
}

AssemblyBlock *IntegerLiteralNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;

  a->mov( eax, Dword(Value()) );
  a->mov( ecx, Dword(goatHash("Integer")));
  a->mov( edx, *DispatchOperandFor("Integer", scope->GetSourceFile()));

  a->CommentLastInstruction("Move Integer " + contents + " into eax/ecx/edx");

  return a;
}

// Generates the assembly to push the integer object onto the stack
// for a function call.

AssemblyBlock *IntegerLiteralNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock;

  a->push( Dword(goatHash("Integer")) );
  a->push( *DispatchOperandFor("Integer", scope->GetSourceFile()));
  a->push( Dword(Value()) );

  a->CommentLastInstruction("Push Integer " + contents + " onto stack");

  return a;
}
