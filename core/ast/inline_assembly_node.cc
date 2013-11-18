#include "../goat.h"
#include "../ast_node.h"

void InlineAssemblyNode::Analyse( Scope *_scope) {
  ASTIterator end(NULL);

  scope = _scope;

  for(ASTIterator i = ChildNodes(); i != end; i++) {
    i->Analyse( scope );
  }
}

AssemblyBlock *InlineAssemblyNode::GenerateCode() const {
  AssemblyBlock *a = new AssemblyBlock;
  ASTIterator end(NULL);

  for(ASTIterator i = ChildNodes(); i != end; i++) {
    a->AppendBlock( i->GenerateCode() );
  }

  return a;
}
