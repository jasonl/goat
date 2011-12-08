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
  scope = _scope;

  if(!scope->HasVariable(VariableName()))
  {
	  scope->AddLocalVariable(VariableName());
  }

  firstChild->Analyse( scope );
}

AssemblyBlock *MutableAssignmentNode::GenerateCode()
{
	// Move the rValue into eax/ecx/edx
	AssemblyBlock *a = firstChild->GenerateCode();

	// Now we've got the rValue in eax/ecx/edx, assign it.
	AssemblyBlock *assignmentAsm = target->GenerateAssignmentCode();

	a->AppendBlock(assignmentAsm);
	a->CommentLastInstruction("Assignment to " + VariableName());

	return a;
}
