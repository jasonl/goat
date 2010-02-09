#include "lexer.h"
#include "ast.h"

ASTNode::ASTNode( enum NODE_TYPE _type) {
  type = _type;
}
