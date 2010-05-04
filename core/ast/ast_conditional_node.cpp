#include "../ast_node.h"

ASTConditionalNode::ASTConditionalNode() : ASTNode( ASTNode::Conditional ) {
}

void ASTConditionalNode::AddExpression( ASTNode *_expr ) {
  append( _expr );
  expression = _expr;
}

void ASTConditionalNode::AddIfBlock( ASTBlockNode *_ifBlock ) {
  append( _ifBlock );
  ifBlock = _ifBlock;
}

void ASTConditionalNode::AddElseBlock( ASTBlockNode *_elseBlock ) {
  append( _elseBlock );
  elseBlock = _elseBlock;
}

void ASTConditionalNode::Analyse( Scope *scope ) {
}
