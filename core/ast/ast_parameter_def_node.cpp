#include "../ast_node.h"

ASTParameterDefNode::ASTParameterDefNode( std::string _identifier ) : ASTNode( ASTNode::ParameterDef ) {
  identifier = _identifier;
}
