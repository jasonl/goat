#include "../ast_node.h"

void VariableNode::Analyse( Scope *_scope ) {
  scope = _scope;

  // If the variable doesn't exist, transform it into a function call
  // and deal with it at runtime.
  if( !scope->HasVariable(name) ) {
    FunctionCallNode *fc = new FunctionCallNode(name);
    SelfNode *sn = new SelfNode();
    fc->AddReceiver( sn );
    parent->ReplaceChild( this, fc );
    fc->Analyse(scope);

    delete this;
    return;
  }
}

AssemblyBlock *VariableNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock();

  a->mov( eax, scope->GeneratePayloadOperand(name) );
  a->mov( ecx, scope->GenerateTypeHashOperand(name) );
  a->mov( edx, scope->GenerateDispatchOperand(name) );

  a->CommentLastInstruction("Move " + name + " into eax/ecx/edx");

  return a;
}

AssemblyBlock *VariableNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock();

  a->push( Dword(scope->GenerateTypeHashOperand(name)) );
  a->push( Dword(scope->GenerateDispatchOperand(name)) );
  a->push( Dword(scope->GeneratePayloadOperand(name)) );

  a->CommentLastInstruction("Push " + name + " on to stack");

  return a;
}
