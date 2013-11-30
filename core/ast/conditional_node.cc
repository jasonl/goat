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

void ConditionalNode::GenerateCode(AssemblyBlock* a) const 
{
	std::string isBoolean = scope->GenerateUniqueLabel("is_boolean");
	std::string endConditional = scope->GenerateUniqueLabel("end_conditional");
	std::string elseLabel = scope->GenerateUniqueLabel("else_clause");

	// Generate the code to put the result of the expressing in eax/ecx/edx
	expression->GenerateCode(a);

	// If the eax/edx/ecs isn't a boolean, try to convert it
	a->cmp(ecx, Dword(goatHash("Boolean")));
	a->je(*new Operand(isBoolean));
	a->mov(ebx, Dword(goatHash("asBoolean")));
	a->call(edx);
  
	// eax/ecx/edx now has a boolean in it.
	a->test(eax, eax);
	a->LabelLastInstruction(isBoolean);

	// Jump based on the result.
	if (elseBlock) {
		a->jz(*new Operand(elseLabel));
	} else {
		a->jz(*new Operand(endConditional));
	}

	// Generate the code for the true case
	ifBlock->GenerateCode(a);
	a->jmp(*new Operand(endConditional));

	if (elseBlock) {
		AssemblyBlock *elseClauseAsm = new AssemblyBlock;
		elseBlock->GenerateCode(elseClauseAsm);
		elseClauseAsm->LabelFirstInstruction(elseLabel);
		a->AppendBlock(elseClauseAsm); // Implicit delete of elseClauseAsm
	}

	a->AddHangingLabel(endConditional);	
}
