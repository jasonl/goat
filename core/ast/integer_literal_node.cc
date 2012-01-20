#include <cstdlib>
#include "../goat.h"
#include "../ast_node.h"

// Generates the code to put the integer object into EAX/ECX/EDX.

AssemblyBlock *IntegerLiteralNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;

  // All integer values are 32-bit signed values
  int32_t val = atol( contents.c_str() );


  a->mov( eax, Dword(val) );
  a->mov( ecx, Dword(goatHash("Integer")));
  a->mov( edx, *DispatchOperandFor("Integer", scope->GetSourceFile()));

  a->CommentLastInstruction("Move Integer " + contents + " into eax/ecx/edx");

  return a;
}

// Generates the assembly to push the integer object onto the stack
// for a function call.

AssemblyBlock *IntegerLiteralNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock;

  // All integer values are 32-bit signed values
  int32_t val = atol( contents.c_str() );

  a->push( Dword(goatHash("Integer")) );
  a->push( *DispatchOperandFor("Integer", scope->GetSourceFile()));
  a->push( Dword(val) );

  a->CommentLastInstruction("Push Integer " + contents + " onto stack");

  return a;
}
