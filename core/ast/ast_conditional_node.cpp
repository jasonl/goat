#include "../ast_node.h"

ASTConditionalNode::ASTConditionalNode() : ASTNode( ASTNode::Conditional ) {
  ifBlock = NULL;
  elseBlock = NULL;
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
  ASTIterator end(NULL);

  for( ASTIterator i = ChildNodes(); i != end; ++i ) {
    i->Analyse( scope );
  }
}
