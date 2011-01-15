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
  std::string varName = Content();
  
  a->mov( eax, scope->GeneratePayloadOperand(varName) );
  a->mov( ecx, scope->GenerateTypeHashOperand(varName) );
  a->mov( edx, scope->GenerateDispatchOperand(varName) );

  a->CommentLastInstruction("Move " + varName + " into eax/ecx/edx");

  return a;
}

AssemblyBlock *VariableNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock();
  std::string varName = Content();

  a->push( Dword(scope->GenerateTypeHashOperand(varName)) );
  a->push( Dword(scope->GenerateDispatchOperand(varName)) );
  a->push( Dword(scope->GeneratePayloadOperand(varName)) );

  a->CommentLastInstruction("Push " + varName + " on to stack");

  return a;
}
