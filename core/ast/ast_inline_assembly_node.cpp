#include "../ast_node.h"

ASTInlineAssemblyNode::ASTInlineAssemblyNode(): 
  ASTNode( ASTNode::InlineAssembly ) {  
}

void ASTInlineAssemblyNode::Analyse( Scope *_scope) {
  ASTIterator end(NULL);

  scope = _scope;

  for(ASTIterator i = ChildNodes(); i != end; i++) {
    i->Analyse( scope );
  }
}

AssemblyBlock *ASTInlineAssemblyNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;
  ASTIterator end(NULL);

  for(ASTIterator i = ChildNodes(); i != end; i++) {
    a->AppendBlock( i->GenerateCode() );
  }

  return a;
}
