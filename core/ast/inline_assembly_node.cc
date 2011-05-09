#include "../ast_node.h"

InlineAssemblyNode::InlineAssemblyNode(): 
  ASTNode( ASTNode::InlineAssembly ) {  
}

void InlineAssemblyNode::Analyse( Scope *_scope) {
  ASTIterator end(NULL);

  scope = _scope;

  for(ASTIterator i = ChildNodes(); i != end; i++) {
    i->Analyse( scope );
  }
}

AssemblyBlock *InlineAssemblyNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;
  ASTIterator end(NULL);

  for(ASTIterator i = ChildNodes(); i != end; i++) {
    a->AppendBlock( i->GenerateCode() );
  }

  return a;
}
