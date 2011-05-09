#include <string>
#include <list>
#include "../ast_node.h"
#include "../lexer.h"
/*
  A Function definition contains a number of child nodes:
  - A number of ParameterDef nodes, each corresponding to one of the parameters
    declared for the function;
  - A Block node, which contains the function's body.
*/

FunctionDefNode::FunctionDefNode() : ASTNode( ASTNode::FunctionDef ) {
  scope = NULL;
  bodyAsm = new AssemblyBlock;
}

FunctionDefNode::~FunctionDefNode() {
  if( scope ) delete scope;
  if( bodyAsm ) delete bodyAsm;
}

ASTIterator FunctionDefNode::ParameterDefs() {
  return ASTIterator( firstChild );
}

ASTIterator FunctionDefNode::BodyNodes() {
  return ASTIterator( body );
}

void FunctionDefNode::AddBody( ASTNode* _body ) {
  append( _body );
  body = _body;
}

void FunctionDefNode::AddParameterDef( ASTNode *_param ) {
  append( _param );
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

  // Now analyse the function body
  body->Analyse( scope );
}

AssemblyBlock *FunctionDefNode::GenerateCode() {
  ASTIterator end( NULL );
  std::string functionName;
  uint32_t bytesForLocals;

  bodyAsm->push( ebp );
  bodyAsm->mov( ebp, esp );

  bytesForLocals = scope->GetLocalVariableCount() * 12;
  bodyAsm->sub( esp, *new Operand(bytesForLocals) );

  // Move self into the locals from the registers, so we're free to nuke eax/ecx/edx
  // TODO: Don't generate this if self isn't referenced in the code.
  bodyAsm->mov( scope->GeneratePayloadOperand("self"), eax );
  bodyAsm->mov( scope->GenerateTypeHashOperand("self"), ecx );
  bodyAsm->mov( scope->GenerateDispatchOperand("self"), edx );

  bodyAsm->CommentLastInstruction("Move self passed in registers to locals");

  ImmutableAssignmentNode *p = dynamic_cast<ImmutableAssignmentNode*>(parent);

  if(p && (p->VariableName().length() > 0)) {
    functionName = p->VariableName();
  } else {
    functionName = scope->GenerateUniqueLabel("anonymous_fn");
  }

  bodyAsm->LabelFirstInstruction( functionName );

  for( ASTIterator i = BodyNodes(); i != end; i++ ) {
    bodyAsm->AppendBlock( i->GenerateCode() );
  }

  // Return a default null if code execution reaches here
  bodyAsm->mov( eax, Dword(0) );
  bodyAsm->mov( ecx, Dword(goatHash("Null")));
  bodyAsm->mov( edx, *DispatchOperandFor("Null", scope->GetSourceFile()));

  bodyAsm->add( esp, *new Operand(scope->GetLocalVariableCount() * 12));
  bodyAsm->mov( esp, ebp );
  bodyAsm->pop( ebp );
  bodyAsm->ret();

  // Generate code for the actual function object
  AssemblyBlock *a = new AssemblyBlock;

  a->mov( eax, *new Operand(functionName));
  a->mov( ecx, Dword(goatHash("Function")));
  a->mov( edx, *DispatchOperandFor("Null", scope->GetSourceFile())); //TODO This needs to reference a label

  a->CommentLastInstruction("Function object for " + functionName);

  return a;
}

AssemblyBlock *FunctionDefNode::GetAuxiliaryCode() {
  ASTIterator end(NULL);

  for( ASTIterator i = ChildNodes(); i != end; i++) {
    bodyAsm->AppendBlock( i->GetAuxiliaryCode() );
  }

  return bodyAsm;
}
