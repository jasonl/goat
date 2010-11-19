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
  std::string varName = Content();
  
  a->MOV( eax, scope->GeneratePayloadOperand(varName) );
  a->MOV( ecx, scope->GenerateTypeHashOperand(varName) );
  a->MOV( edx, scope->GenerateDispatchOperand(varName) );

  a->CommentLastInstruction("Move " + varName + " into eax/ecx/edx");

  return a;
}

AssemblyBlock *VariableNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock();
  std::string varName = Content();

  a->PUSH( Dword(scope->GenerateTypeHashOperand(varName)) );
  a->PUSH( Dword(scope->GenerateDispatchOperand(varName)) );
  a->PUSH( Dword(scope->GeneratePayloadOperand(varName)) );

  a->CommentLastInstruction("Push " + varName + " on to stack");

  return a;
}
