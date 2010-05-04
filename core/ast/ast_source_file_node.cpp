#include "../ast_node.h"

ASTSourceFileNode::ASTSourceFileNode() : ASTNode( ASTNode::SourceFile ) {
}

void ASTSourceFileNode::Analyse( Scope *scope ) {
  ASTIterator end(NULL);

  for( ASTIterator i = ChildNodes(); i != end; i++ ) {
    i->Analyse( scope );
  } 
}
