#include "../ast_node.h"
#include "../lexer.h"

InstructionNode::InstructionNode( TokenIterator &_token ): 
  ASTNode( ASTNode::Instruction ) {
  token = &(*_token);
}
