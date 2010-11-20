#include <string>
#include <list>
#include "../ast_node.h"
#include "../lexer.h"
/*
  A Function definition contains a number of child nodes:
  - A number of ParameterDef nodes, each corresponding to one of the parameters
    declared for the function;
  - A Block node, which contains the function's body.
*/

FunctionDefNode::FunctionDefNode() : ASTNode( ASTNode::FunctionDef ) {
  scope = NULL;
  bodyAsm = new AssemblyBlock;
}

FunctionDefNode::~FunctionDefNode() {
  if( scope ) delete scope;
  if( bodyAsm ) delete bodyAsm;
}

ASTIterator FunctionDefNode::ParameterDefs() {
  return ASTIterator( firstChild );
}

ASTIterator FunctionDefNode::BodyNodes() {
  return ASTIterator( body );
}

void FunctionDefNode::AddBody( ASTNode* _body ) {
  append( _body );
  body = _body;
}

void FunctionDefNode::AddParameterDef( ASTNode *_param ) {
  append( _param );
}

void FunctionDefNode::Analyse( Scope *_scope ) {
  ASTIterator endParams( body ); // body is first node after last ParameterDef
  
  // Reverse the list of params
  std::list<ASTNode> paramsList;
  
  for(ASTIterator i = ParameterDefs(); i != endParams; i++) {
    paramsList.push_front( *i );
  }

  // Create a new lexical scope for the function body
  scope = new Scope( _scope );

  // Add the parameters to the scope
  for(std::list<ASTNode>::iterator i = paramsList.begin(); i != paramsList.end(); i++) {
    if( scope->HasVariable( i->Content() )) {
      // TODO: Raise an error/warning when we find a name collision between the parameter name
      // and anything else. Warning where the name is found not in the exact same scope, (e.g.
      // a parameter named the same as a global variable) and an error when in the same scope
      // (e.g. When a function λ(param,param) is defined.
    } else {
      scope->AddParameterVariable( i->Content() );
    }
  }

  // Add the self variable - passed in registers, but we'll usually need to move it
  // to the locals.
  scope->AddLocalVariable( "self" );

  // Now analyse the function body
  body->Analyse( scope );
}

AssemblyBlock *FunctionDefNode::GenerateCode() {
  ASTIterator end( NULL );
  std::string functionName;

  bodyAsm->PUSH( ebp );
  bodyAsm->MOV( ebp, esp );

  // Move self into the locals from the registers, so we're free to nuke eax/ecx/edx
  // TODO: Don't generate this if self isn't referenced in the code.
  bodyAsm->MOV( scope->GeneratePayloadOperand("self"), eax );
  bodyAsm->MOV( scope->GenerateTypeHashOperand("self"), ecx );
  bodyAsm->MOV( scope->GenerateDispatchOperand("self"), edx );

  bodyAsm->CommentLastInstruction("Move self passed in registers to locals");

  if(parent->HasContent()) {
    functionName = parent->Content();
  } else {
    functionName = scope->GenerateUniqueLabel("anonymous_fn");
  }

  bodyAsm->LabelFirstInstruction( functionName );

  for( ASTIterator i = BodyNodes(); i != end; i++ ) {
    bodyAsm->AppendBlock( i->GenerateCode() );
  }

  // Return a default null if code execution reaches here
  bodyAsm->MOV( eax, Dword(0) );
  bodyAsm->MOV( ecx, Dword(goatHash("Null")));
  bodyAsm->MOV( edx, Dword(0) ); //TODO: This needs to reference a label

  bodyAsm->POP(ebp);
  bodyAsm->RET();

  // Generate code for the actual function object
  AssemblyBlock *a = new AssemblyBlock;

  a->MOV( eax, *new Operand(functionName));
  a->MOV( ecx, Dword(goatHash("Function")));
  a->MOV( edx, Dword(0) ); //TODO This needs to reference a label
  
  a->CommentLastInstruction("Function object for " + functionName);

  return a;
} 

AssemblyBlock *FunctionDefNode::GetAuxiliaryCode() {
  ASTIterator end(NULL);
  
  for( ASTIterator i = ChildNodes(); i != end; i++) {
    bodyAsm->AppendBlock( i->GetAuxiliaryCode() );
  }

  return bodyAsm;
}
