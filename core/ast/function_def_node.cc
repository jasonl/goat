#include "../goat.h"
#include "../ast_node.h"
#include "../lexer.h"
/*
  A Function definition contains a number of child nodes:
  - A number of ParameterDef nodes, each corresponding to one of the parameters
    declared for the function;
  - A Block node, which contains the function's body.
*/

FunctionDefNode::FunctionDefNode()
{
	scope = NULL;
	paramCount = 0;
}

FunctionDefNode::~FunctionDefNode() 
{
  if( scope ) delete scope;
}

ASTIterator FunctionDefNode::ParameterDefs() const {
  return ASTIterator( firstChild );
}

ASTIterator FunctionDefNode::BodyNodes() const {
  return ASTIterator( body );
}

void FunctionDefNode::AddBody( ASTNode* _body ) {
  AppendChild( _body );
  body = _body;
}

void FunctionDefNode::AddParameterDef( ASTNode *_param )
{
	// Assumes the body has yet to be added
	AppendChild( _param );
	paramCount++;
}

void FunctionDefNode::Analyse( Scope *_scope ) {
  ASTIterator start( NULL );

  // Create a new lexical scope for the function body
  scope = new Scope( _scope );

  // Add the parameters to the scope
  ASTIterator i = ASTIterator(body);

  for(i--; i != start; i--) {
	  ParameterDefNode *param = dynamic_cast<ParameterDefNode*>(&(*i));

	if(param)
	{
		if( scope->HasVariable(param->Name()))
		{
			// TODO: Raise an error/warning when we find a name collision between the parameter name
			// and anything else. Warning where the name is found not in the exact same scope, (e.g.
			// a parameter named the same as a global variable) and an error when in the same scope
			// (e.g. When a function λ(param,param) is defined.
		} else {
			scope->AddParameterVariable(param->Name());
		}
	}
  }

  // Add the self variable - passed in registers, but we'll usually need to move it
  // to the locals.
  scope->AddLocalVariable( "self" );

  // Generate the function name
  ConstantAssignmentNode *p = dynamic_cast<ConstantAssignmentNode*>(parent);

  if(p && (p->VariableName().length() > 0)) {
    functionName = p->VariableName();
  } else {
    functionName = scope->GenerateUniqueLabel("anonymous_fn");
  }

  // Now analyse the function body
  body->Analyse( scope );
}

void FunctionDefNode::GenerateCode(AssemblyBlock* a) const 
{
	a->mov(eax, *new Operand(functionName));
	a->mov(ecx, Dword(goatHash("Function")));
	a->mov(edx, *DispatchOperandFor("Null", scope->GetSourceFile())); //TODO This needs to reference a label
	a->CommentLastInstruction("Function object for " + functionName);
}

void FunctionDefNode::GetAuxiliaryCode(AssemblyBlock* a) const
{
	ASTIterator end(NULL);
	uint32_t bytesForLocals;

	a->push(ebp);
	a->LabelLastInstruction(functionName);
	a->mov(ebp, esp);
	
	bytesForLocals = scope->GetLocalVariableCount() * 12;
	a->sub(esp, *new Operand(bytesForLocals));
  
	// Move self into the locals from the registers, so we're free to nuke eax/ecx/edx
	// TODO: Don't generate this if self isn't referenced in the code.
	a->mov(scope->GeneratePayloadOperand("self"), eax);
	a->mov(scope->GenerateTypeHashOperand("self"), ecx);
	a->mov(scope->GenerateDispatchOperand("self"), edx);
	a->CommentLastInstruction("Move self passed in registers to locals");

	// Add the actual code for all the statements in the function
	for (ASTIterator i = BodyNodes(); i != end; i++) {
		i->GenerateCode(a);
	}

	// Return a default null if code execution reaches here
	a->mov(eax, Dword(0));
	a->mov(ecx, Dword(goatHash("Null")));
	a->mov(edx, *DispatchOperandFor("Null", scope->GetSourceFile()));
	
	a->mov(esp, ebp);
	a->pop(ebp);
	a->ret();
	
	for (ASTIterator i = ChildNodes(); i != end; i++) {
		i->GetAuxiliaryCode(a);
	}
}
