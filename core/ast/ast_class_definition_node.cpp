#include "../ast_node.h"
#include "../lexer.h"

ASTClassDefinitionNode::ASTClassDefinitionNode( TokenIterator &_token ) : ASTNode( ASTNode::ClassDefinition ) {
  token = &(*_token);
}

void ASTClassDefinitionNode::Analyse( Scope *_scope ) {
  ASTIterator end(NULL);

  scope = new Scope( _scope );

  // Add a class variable for every assignment (including functions)
  for( ASTIterator i = ChildNodes(); i != end; i++ ) {
    // This all depends on the knowledge that only MutableAssignment
    // and ImmutableAssignment ASTNodes can be found in a class body

    if( scope->HasVariable( i->Content()) ) {
      // TODO: Add warning of redefinition
    }

    scope->AddClassVariable( i->Content() );
    i->Analyse( scope );
    
  }
}
