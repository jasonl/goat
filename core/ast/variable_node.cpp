#include "../ast_node.h"

/*
 * VariableNode
 *
 * A node representing the use (not the assignment) of a variable
 *
 */
 

VariableNode::VariableNode( TokenIterator & _token ): 
  ASTNode( ASTNode::Variable ) {
  token = &(*_token);
}

void VariableNode::Analyse( Scope *_scope ) {
  scope = _scope;

  if( scope->HasVariable(Content()) ) {
    
  } else {
    FunctionCallNode *fc = new FunctionCallNode( token );
    ASTThisNode *tn = new ASTThisNode();
    fc->AddReceiver( tn );
    parent->ReplaceChild( this, fc );
    delete this;
    return;
  }
}
