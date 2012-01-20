#include "../goat.h"
#include "../ast_node.h"

void NullLiteralNode::Analyse( Scope *_scope ) {
  scope = _scope;
}

AssemblyBlock *NullLiteralNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock();

  a->mov( eax, Dword(0) );
  a->mov( ecx, Dword(goatHash("Null")));
  a->mov( edx, *DispatchOperandFor("Null", scope->GetSourceFile()));

  a->CommentLastInstruction("Move Null into eax/ecx/edx");

  return a;
}

AssemblyBlock *NullLiteralNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock();

  a->push( Dword(goatHash("Null")));
  a->push( *DispatchOperandFor("Null", scope->GetSourceFile())); //TODO: This needs to reference a label
  a->push( Dword(0) );

  a->CommentLastInstruction("Push Null onto stack");

  return a;
}
