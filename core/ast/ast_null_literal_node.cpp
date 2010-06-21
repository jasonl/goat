#include "../ast_node.h"

ASTNullLiteralNode::ASTNullLiteralNode() : ASTNode( ASTNode::NullLiteral ) {
}

void ASTNullLiteralNode::Analyse( Scope *_scope ) {
  scope = _scope;
}

AssemblyBlock *ASTNullLiteralNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock();

  a->MOV( eax, Dword(0) );
  a->MOV( ecx, Dword(goatHash("Null")));
  a->MOV( edx, Dword(0) ); //TODO: This needs to reference a label

  return a;
}
