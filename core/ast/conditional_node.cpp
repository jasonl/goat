#include "../ast_node.h"

ConditionalNode::ConditionalNode() : ASTNode( ASTNode::Conditional ) {
  ifBlock = NULL;
  elseBlock = NULL;
}

void ConditionalNode::AddExpression( ASTNode *_expr ) {
  append( _expr );
  expression = _expr;
}

void ConditionalNode::AddIfBlock( BlockNode *_ifBlock ) {
  append( _ifBlock );
  ifBlock = _ifBlock;
}

void ConditionalNode::AddElseBlock( BlockNode *_elseBlock ) {
  append( _elseBlock );
  elseBlock = _elseBlock;
}

void ConditionalNode::Analyse( Scope *scope ) {
  ASTIterator end(NULL);

  for( ASTIterator i = ChildNodes(); i != end; ++i ) {
    i->Analyse( scope );
  }
}
