#include "../goat.h"
#include "../ast_node.h"
#include "../lexer.h"
#include "../source_file.h"
#include "../i386/function_labels.h"

void ClassDefinitionNode::Analyse( Scope *_scope ) {
  ASTIterator end(NULL);

  scope = new Scope( _scope );

  // Add a class variable for every assignment (including functions)
  for( ASTIterator i = ChildNodes(); i != end; i++ )
  {
	  ConstantAssignmentNode *m = dynamic_cast<ConstantAssignmentNode*>(&(*i));
	  // This all depends on the knowledge that only MutableAssignment
	  // and ImmutableAssignment ASTNodes can be found in a class body

	  if(m && scope->HasVariable(m->VariableName())) {
		  // TODO: Add warning of redefinition
	  }

	  i->Analyse( scope );
  }
}

void ClassDefinitionNode::AddClassVariable(const std::string &name)
{
	classVars[name] = lastVarPosition;
	lastVarPosition++;
}

int ClassDefinitionNode::ClassVariablePosition(const std::string &name) const
{
	ClassVarMap::const_iterator ci = classVars.find(name);
	if(ci != classVars.end())
	{
		return ci->second;
	} else {
		return -1;
	}
}

AssemblyBlock *ClassDefinitionNode::GenerateCode() {
  ASTIterator end(NULL);
  AssemblyBlock *a = new AssemblyBlock;
  AssemblyBlock *fn;
  AssemblyBlock *dispatch = new AssemblyBlock;

  for(ASTIterator i = ChildNodes(); i != end; i++) {
	  MethodAssignmentNode *m = dynamic_cast<MethodAssignmentNode*>(&(*i));

	  if(m)
	  {
		  m->GenerateCode();
		  fn = m->GetAuxiliaryCode();
		  fn->LabelFirstInstruction(GenerateFunctionLabel(m->Name(), name));

		  dispatch->cmp(ebx, Dword(goatHash(m->Name())));
		  dispatch->je(*new Operand(GenerateFunctionLabel(m->Name(), name)));

		  a->AppendBlock(fn);
	  }

	  ClassMethodAssignmentNode *c = dynamic_cast<ClassMethodAssignmentNode*>(&(*i));
	  if (c)
	  {
		  std::string cfnLabel = GenerateClassMethodLabel(c->Name(), name);

		  c->GenerateCode();
		  fn = c->GetAuxiliaryCode();
		  fn->LabelFirstInstruction(cfnLabel);
		  fn->PrependItem(new GlobalSymbol(cfnLabel));
		  scope->GetSourceFile()->AddGlobalSymbol(cfnLabel);
		  a->AppendBlock(fn);
	  }
  }

  // If a method isn't found, exit with error code 5
  // TODO: Write an actual error message.
  dispatch->push(Dword(5));
  dispatch->mov(eax, *new Operand(0x01));
  dispatch->sub(esp, *new Operand(0x04));
  dispatch->_int(*new Operand(0x80));

  dispatch->CommentLastInstruction("Exit with code 5 if not found");

  std::string dispatchLabel = DispatchLabelNameFor(name);

  dispatch->LabelFirstInstruction(DispatchLabelNameFor(name));
  dispatch->PrependItem(new GlobalSymbol(dispatchLabel));
  scope->GetSourceFile()->AddGlobalSymbol(dispatchLabel);

  dispatch->AppendBlock(a);
  return dispatch;
}

AssemblyBlock *ClassDefinitionNode::GetAuxiliaryCode() {
  return new AssemblyBlock;
}

std::string GenerateFunctionLabel( const std::string functionName, const std::string className ) {
  std::string fnName = "__" + className + "_" + functionName;
  return SanitizeLabel(fnName);
}

std::string GenerateClassMethodLabel( const std::string functionName, const std::string className ) {
  std::string cfnName = "c_" + className + "_" + functionName;
  return SanitizeLabel(cfnName);
}
