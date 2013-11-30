#include "../goat.h"
#include "../ast_node.h"

MutableAssignmentNode::MutableAssignmentNode(AssignmentTargetNode *_target, ASTNode *_rValue)
{
	AppendChild(_target);
	AppendChild(_rValue);

	target = _target;
	rValue = _rValue;
}

void MutableAssignmentNode::Analyse( Scope *_scope )
{
	ASTIterator end(NULL);
	scope = _scope;

	if(!scope->HasVariable(VariableName()))
		scope->AddLocalVariable(VariableName());

	for( ASTIterator i = ChildNodes(); i != end; i++)
		i->Analyse(_scope);
}

void MutableAssignmentNode::GenerateCode(AssemblyBlock* a) const
{
	// Move the rValue into eax/ecx/edx
	rValue->GenerateCode(a);

	// Now we've got the rValue in eax/ecx/edx, assign it.
	target->GenerateAssignmentCode(a);

	a->CommentLastInstruction("Assignment to " + VariableName());
}
