#include "../ast_node.h"

ASTBlockNode::ASTBlockNode() : ASTNode( ASTNode::Block ) {
  
}

void ASTBlockNode::Analyse( Scope *_scope) {
  ASTIterator end(NULL);

  scope = _scope;

  for(ASTIterator i = ChildNodes(); i != end; i++) {
    i->Analyse( scope );
  }
}
