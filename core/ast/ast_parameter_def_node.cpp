#include "../ast_node.h"

ASTParameterDefNode::ASTParameterDefNode( TokenIterator &_token ) : ASTNode( ASTNode::ParameterDef ) {
  token = &(*_token);
}

void ASTParameterDefNode::Analyse( Scope *_scope ) {
  scope = _scope;

  if( scope->HasParameterVariable( Content() )) {
    // TODO: Error! Duplicate Parameter Name
  } else {
    scope->AddParameterVariable( Content() );
  }
}

