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

  // If the variable doesn't exist, transform it into a function call
  // and deal with it at runtime.
  if( !scope->HasVariable(Content()) ) {
    FunctionCallNode *fc = new FunctionCallNode( token );
    ASTThisNode *tn = new ASTThisNode();
    fc->AddReceiver( tn );
    parent->ReplaceChild( this, fc );
    delete this;
    return;
  }
}

AssemblyBlock *VariableNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock();
  
  a->MOV( eax, scope->GeneratePayloadOperand(Content()) );
  a->MOV( ecx, scope->GenerateTypeHashOperand(Content()) );
  a->MOV( edx, scope->GenerateDispatchOperand(Content()) );

  return a;
}

AssemblyBlock *VariableNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock();

  a->PUSH( scope->GenerateTypeHashOperand(Content()) );
  a->PUSH( scope->GenerateDispatchOperand(Content()) );
  a->PUSH( scope->GeneratePayloadOperand(Content()) );

  return a;
}
