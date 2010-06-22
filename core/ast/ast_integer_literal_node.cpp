#include <cstdlib>
#include "../ast_node.h"

ASTIntegerLiteralNode::ASTIntegerLiteralNode( TokenIterator &_token ) : ASTNode( ASTNode::IntegerLiteral ) {
  token = &(*_token);
}

void ASTIntegerLiteralNode::Analyse( Scope *_scope ) {
  scope = _scope;
}

AssemblyBlock *ASTIntegerLiteralNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;

  // All integer values are 32-bit signed values
  int32_t val = atol( Content().c_str() );


  a->MOV( eax, Dword(val) );
  a->MOV( ecx, Dword(goatHash("Integer")));
  a->MOV( edx, Dword(0)); // TODO: This needs to reference a label

  return a;
}
