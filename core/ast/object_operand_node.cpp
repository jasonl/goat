#include "../goat.h"
#include "../ast_node.h"
#include "../lexer.h" 

ObjectOperandNode::ObjectOperandNode( Token &_token ) : OperandNode(ASTNode::ObjectOperand) {
  token = &_token;
}

void ObjectOperandNode::SetPropertyName( std::string _propertyName ) {
  propertyName = _propertyName;
}

Operand *ObjectOperandNode::GenerateOperand() {
  if(!scope->HasVariable(token->Content())) {
    goatError(0, "No variable found in local scope");
  }

  if(propertyName == "payload") {
    return &(scope->GeneratePayloadOperand(token->Content()));
  }

  if(propertyName == "dispatch") {
    return &(scope->GenerateDispatchOperand(token->Content()));
  }

  if(propertyName == "type") {
    return &(scope->GenerateTypeHashOperand(token->Content()));
  }

  goatError(0, "Invalid object property found in inline assembly");
  return NULL;
}
