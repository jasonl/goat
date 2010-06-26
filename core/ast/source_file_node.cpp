#include "../ast_node.h"

SourceFileNode::SourceFileNode() : ASTNode( ASTNode::SourceFile ) {
}

void SourceFileNode::Analyse( Scope *scope ) {
  ASTIterator end(NULL);

  for( ASTIterator i = ChildNodes(); i != end; i++ ) {
    i->Analyse( scope );
  } 
}

AssemblyBlock *SourceFileNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;
  ASTIterator end(NULL);

  for( ASTIterator i = ChildNodes(); i != end; i++ ) {
    a->AppendBlock( i->GenerateCode() );
  }

  return a;
}
