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
