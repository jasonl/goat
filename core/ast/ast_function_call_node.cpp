#include "../ast_node.h"

ASTFunctionCallNode::ASTFunctionCallNode( TokenIterator &_token ) : ASTNode( ASTNode::FunctionCall ) {
  token = &(*_token);
}

void ASTFunctionCallNode::Analyse(Scope *_scope) {
  ASTIterator end(NULL);
  scope = _scope;

  if( Receiver() == NULL ) {
    ASTThisNode *_this = new ASTThisNode();
    AddReceiver( _this );
  }

  for( ASTIterator i = ChildNodes(); i != end; ++i ) {
    i->Analyse( scope );
  }
}

void ASTFunctionCallNode::AddReceiver( ASTNode *_receiver ) {
  // TODO: This should check that there isn't already a receiver
  InsertFirstChild( _receiver );
  receiver = receiver;
}
