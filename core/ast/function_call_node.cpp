#include "../ast_node.h"

FunctionCallNode::FunctionCallNode( TokenIterator &_token ): 
  ASTNode( ASTNode::FunctionCall ) {
  token = &(*_token);
}

FunctionCallNode::FunctionCallNode( Token *_token ):
  ASTNode( ASTNode::FunctionCall ) {
  token = _token;
}

void FunctionCallNode::Analyse(Scope *_scope) {
  ASTIterator end(NULL);
  scope = _scope;

  // Add the implicit this receiver if it doesn't exist
  if( Receiver() == NULL ) {
    ASTThisNode *_this = new ASTThisNode();
    AddReceiver( _this );
  }
  

  for( ASTIterator i = ChildNodes(); i != end; ++i ) {
    i->Analyse( scope );
  }
}

void FunctionCallNode::AddReceiver( ASTNode *_receiver ) {
  // TODO: This should check that there isn't already a receiver
  InsertFirstChild( _receiver );
  receiver = _receiver;
}

AssemblyBlock *FunctionCallNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;
  ASTIterator end(NULL);

  // Put the receiver (i.e. this ) into EAX/ECX/EDX
  a->AppendBlock( receiver->GenerateCode() );

  // Push the parameters onto the stack
  for( ASTIterator i = ChildNodes(); i != end; i++ ) {
    if( i->Type() == ASTNode::Parameter ) {
      a->AppendBlock( i->PushOntoStack() );
    }
  }
  a->MOV( ecx, Dword(goatHash( Content() )));
  a->CALL( edx );

  return a;
}

AssemblyBlock *FunctionCallNode::PushOntoStack() {
  AssemblyBlock *a = GenerateCode();

  a->PUSH( ecx );   // Type Hash of the object
  a->PUSH( edx );   // Dispatch Fnof the object
  a->PUSH( eax );   // Object payload

  return a;
}
