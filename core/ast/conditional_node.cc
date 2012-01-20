#include "../goat.h"
#include "../ast_node.h"

ConditionalNode::ConditionalNode() : ASTNode()
{
	ifBlock = NULL;
	elseBlock = NULL;
}

void ConditionalNode::AddExpression( ASTNode *_expr ) {
  AppendChild( _expr );
  expression = _expr;
}

void ConditionalNode::AddIfBlock( BlockNode *_ifBlock ) {
  AppendChild( _ifBlock );
  ifBlock = _ifBlock;
}

void ConditionalNode::AddElseBlock( BlockNode *_elseBlock ) {
  AppendChild( _elseBlock );
  elseBlock = _elseBlock;
}

void ConditionalNode::Analyse( Scope *_scope ) {
  scope = _scope;
  ASTIterator end(NULL);

  for( ASTIterator i = ChildNodes(); i != end; ++i ) {
    i->Analyse( scope );
  }
}

AssemblyBlock *ConditionalNode::GenerateCode() {
  AssemblyBlock *a = expression->GenerateCode();
  AssemblyBlock *elseClauseAsm = NULL;

  std::string isBoolean = scope->GenerateUniqueLabel("is_boolean");
  std::string endConditional = scope->GenerateUniqueLabel("end_conditional");
  std::string elseLabel = scope->GenerateUniqueLabel("else_clause");

  // If the expression isn't a boolean, try to convert it
  a->cmp( ecx, Dword(goatHash("Boolean")));
  a->je( *new Operand(isBoolean) );
  a->mov( ebx, Dword(goatHash("asBoolean")));
  a->call( edx );

  // eax/ecx/edx now has a boolean in it.
  a->test( eax, eax );
  a->LabelLastInstruction( isBoolean );

  if( elseBlock ) {
    a->jz( *new Operand(elseLabel) );
    a->AppendBlock( ifBlock->GenerateCode() );
    a->jmp( *new Operand(endConditional) );

    elseClauseAsm = elseBlock->GenerateCode();
    elseClauseAsm->LabelFirstInstruction( elseLabel );
    a->AppendBlock( elseClauseAsm );

    a->AddHangingLabel( endConditional );
  } else {
    a->jz( *new Operand(endConditional) );
    a->AppendBlock( ifBlock->GenerateCode() );
    a->AddHangingLabel( endConditional );
    }

  return a;
}
