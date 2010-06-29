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
  receiver = _receiver;
}

AssemblyBlock *ASTFunctionCallNode::GenerateCode() {
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
  a->JMP( edx );

  return a;
}

AssemblyBlock *ASTFunctionCallNode::PushOntoStack() {
  AssemblyBlock *a = GenerateCode();

  a->PUSH( ecx );   // Type Hash of the object
  a->PUSH( edx );   // Dispatch Fnof the object
  a->PUSH( eax );   // Object payload

  return a;
}
