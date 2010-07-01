#include "../ast_node.h"

NullLiteralNode::NullLiteralNode(): 
  ASTNode( ASTNode::NullLiteral ) {
}

void NullLiteralNode::Analyse( Scope *_scope ) {
  scope = _scope;
}

AssemblyBlock *NullLiteralNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock();

  a->MOV( eax, Dword(0) );
  a->MOV( ecx, Dword(goatHash("Null")));
  a->MOV( edx, Dword(0) ); //TODO: This needs to reference a label

  return a;
}

AssemblyBlock *NullLiteralNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock();

  a->PUSH( Dword(goatHash("Null")));
  a->PUSH( Dword(0) ); //TODO: This needs to reference a label
  a->PUSH( Dword(0) );

  return a;
}
