#include "../ast_node.h"

void ParameterNode::Analyse( Scope *_scope ) {
  ASTIterator end(NULL);

  scope = _scope;

  for(ASTIterator i = ChildNodes(); i != end; i++) {
    i->Analyse( scope );
  }
}

// Generates the code to push the parameter onto the stack for a
// function call.
AssemblyBlock *ParameterNode::PushOntoStack() {
  return ChildNodes()->PushOntoStack();
}
