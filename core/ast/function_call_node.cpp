#include "../ast_node.h"

FunctionCallNode::FunctionCallNode( TokenIterator &_token ): 
  ASTNode( ASTNode::FunctionCall ) {
  token = &(*_token);
  receiver = NULL;
}

FunctionCallNode::FunctionCallNode( Token *_token ):
  ASTNode( ASTNode::FunctionCall ) {
  token = _token;
  receiver = NULL;
}

void FunctionCallNode::Analyse(Scope *_scope) {
  ASTIterator end(NULL);
  scope = _scope;

  // Add the implicit this receiver if it doesn't exist
  if( Receiver() == NULL ) {
    SelfNode *self = new SelfNode();
    AddReceiver( self );
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
  uint32_t paramCount = 0;

  // Push the parameters onto the stack
  for( ASTIterator i = ChildNodes(); i != end; i++ ) {
    if( i->Type() == ASTNode::Parameter ) {
      a->AppendBlock( i->PushOntoStack() );
      paramCount++;
    }
  }

  // Put the receiver (i.e. this ) onto eax/ecx/edx
  a->AppendBlock( receiver->GenerateCode() );

  a->mov( ecx, Dword(goatHash( Content() )));
  a->call( edx );  
  a->CommentLastInstruction( "Function Call: " + Content() );

  // If we've passed any parameters on the stack, release the space on return
  if(paramCount > 0) {
    a->add(esp, *new Operand(paramCount * 12));
  }
  return a;
}

AssemblyBlock *FunctionCallNode::PushOntoStack() {
  AssemblyBlock *a = GenerateCode();

  a->push( ecx );   // Type Hash of the object
  a->push( edx );   // Dispatch Fnof the object
  a->push( eax );   // Object payload

  return a;
}
