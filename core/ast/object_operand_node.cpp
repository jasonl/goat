#include "../ast_node.h"
#include "../lexer.h"

ObjectOperandNode::ObjectOperandNode( TokenIterator &_token ) : OperandNode(ASTNode::ObjectOperand) {
  token = &(*_token);
}

void ObjectOperandNode::SetPropertyName( std::string _propertyName ) {
  propertyName = _propertyName;
}

Operand *ObjectOperandNode::GenerateOperand() {
  return NULL;
}
