#include "../ast_node.h"

NullLiteralNode::NullLiteralNode(): 
  ASTNode( ASTNode::NullLiteral ) {
}

void NullLiteralNode::Analyse( Scope *_scope ) {
  scope = _scope;
}

AssemblyBlock *NullLiteralNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock();

  a->mov( eax, Dword(0) );
  a->mov( ecx, Dword(goatHash("Null")));
  a->mov( edx, Dword(0) ); //TODO: This needs to reference a label

  a->CommentLastInstruction("Move Null into eax/ecx/edx");

  return a;
}

AssemblyBlock *NullLiteralNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock();

  a->push( Dword(goatHash("Null")));
  a->push( Dword(0) ); //TODO: This needs to reference a label
  a->push( Dword(0) );

  a->CommentLastInstruction("Push Null onto stack");

  return a;
}
