#include <string>
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
}

FunctionDefNode::~FunctionDefNode() {
  if( scope ) delete scope;
}

ASTIterator FunctionDefNode::ParameterDefs() {
  return ASTIterator( firstChild );
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

  // Create a new lexical scope for the function body
  scope = new Scope( _scope );

  // Add the parameters to the scope
  for(ASTIterator i = ParameterDefs(); i != endParams; i++) {
    if( scope->HasVariable( i->Content() )) {
      // TODO: Raise an error/warning when we find a name collision between the parameter name
      // and anything else. Warning where the name is found not in the exact same scope, (e.g.
      // a parameter named the same as a global variable) and an error when in the same scope
      // (e.g. When a function λ(param,param) is defined.
    } else {
      scope->AddParameterVariable( i->Content() );
    }
  }

  // Now analyse the function body
  body->Analyse( scope );
}