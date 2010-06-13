#include "../ast_node.h"
#include "../lexer.h"

ASTDirectOperandNode::ASTDirectOperandNode( TokenIterator &_token ): 
  ASTNode( ASTNode::DirectOperand ) {
  token = &(*_token);
}
