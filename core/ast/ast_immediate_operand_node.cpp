#include "../ast_node.h"
#include "../lexer.h"

ASTImmediateOperandNode::ASTImmediateOperandNode( TokenIterator &_token ) : 
  ASTNode( ASTNode::ImmediateOperand ) {
  token = &(*_token);
}
