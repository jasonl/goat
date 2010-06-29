#include "../ast_node.h"

ParameterNode::ParameterNode() : ASTNode( ASTNode::Parameter ) {
}

void ParameterNode::Analyse( Scope *scope ) {
}

// Generates the code to push the parameter onto the stack for a 
// function call.
AssemblyBlock *ParameterNode::PushOntoStack() {
  return ChildNodes()->PushOntoStack();
}
