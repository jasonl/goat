#include "../ast_node.h"

ASTParameterDefNode::ASTParameterDefNode( TokenIterator &_token ) : ASTNode( ASTNode::ParameterDef ) {
  token = &(*_token);
}
