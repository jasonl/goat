#include "../ast_node.h"

/*
 * VariableNode
 *
 * A node representing the use (not the assignment) of a variable
 *
 */
 

VariableNode::VariableNode( TokenIterator & _token ) : ASTNode( ASTNode::Variable ) {
  token = &(*_token);
}

void VariableNode::Analyse( Scope *scope ) {
}
