#include "../goat.h"
#include "../ast_node.h"

void SelfNode::Analyse( Scope *_scope ) {
  scope = _scope;
}

AssemblyBlock *SelfNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;

  a->mov( eax, scope->GeneratePayloadOperand("self") );
  a->mov( ecx, scope->GenerateTypeHashOperand("self") );
  a->mov( edx, scope->GenerateDispatchOperand("self") );

  a->CommentLastInstruction("Move self into eax/ecx/edx");

  return a;
}

AssemblyBlock *SelfNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock;

  a->push( Dword(scope->GenerateTypeHashOperand("self")) );
  a->push( Dword(scope->GenerateDispatchOperand("self")) );
  a->push( Dword(scope->GeneratePayloadOperand("self")) );

  a->CommentLastInstruction("Push self onto stack");

  return a;
}
