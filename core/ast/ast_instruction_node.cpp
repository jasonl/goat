#include "../ast_node.h"
#include "../lexer.h"

ASTInstructionNode::ASTInstructionNode( TokenIterator &_token ): 
  ASTNode( ASTNode::Instruction ) {
  token = &(*_token);
}
