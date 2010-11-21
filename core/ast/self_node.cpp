#include "../ast_node.h"

SelfNode::SelfNode() : ASTNode( ASTNode::Self ) {
}


void SelfNode::Analyse( Scope *_scope ) {
  scope = _scope;
}

AssemblyBlock *SelfNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;

  a->MOV( eax, scope->GeneratePayloadOperand("self") );
  a->MOV( ecx, scope->GenerateTypeHashOperand("self") );
  a->MOV( edx, scope->GenerateDispatchOperand("self") );

  a->CommentLastInstruction("Move self into eax/ecx/edx");

  return a;
}

AssemblyBlock *SelfNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock;

  a->PUSH( Dword(scope->GenerateTypeHashOperand("self")) );
  a->PUSH( Dword(scope->GenerateDispatchOperand("self")) );
  a->PUSH( Dword(scope->GeneratePayloadOperand("self")) );

  a->CommentLastInstruction("Push self onto stack");

  return a;
}
