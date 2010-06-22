#include "../ast_node.h"

ParameterDefNode::ParameterDefNode( TokenIterator &_token ): 
  ASTNode( ASTNode::ParameterDef ) {
  token = &(*_token);
}

void ParameterDefNode::Analyse( Scope *_scope ) {
  scope = _scope;

  if( scope->HasParameterVariable( Content() )) {
    // TODO: Error! Duplicate Parameter Name
  } else {
    scope->AddParameterVariable( Content() );
  }
}

