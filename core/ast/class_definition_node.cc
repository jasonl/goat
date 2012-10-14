#include "../goat.h"
#include "../ast_node.h"
#include "../lexer.h"
#include "../source_file.h"
#include "../i386/function_labels.h"

void ClassDefinitionNode::Analyse(Scope *_scope)
{
	scope = new Scope(_scope);

	for(ClassMethodIterator i = classMethodNodes.begin(); i != classMethodNodes.end(); i++)
	{
		ClassMethodAssignmentNode *c = *i;
		c->Analyse(scope);
		RegisterClassMethod(c->Name(), c->ParameterCount());
	}

	for(MethodIterator i = methodNodes.begin(); i != methodNodes.end(); i++)
	{
		MethodAssignmentNode *m = *i;
		m->Analyse(scope);
		RegisterMethod(m->Name(), m->ParameterCount());
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
	if (ci != classVars.end())
	{
		return ci->second;
	} else {
		return -1;
	}
}

void ClassDefinitionNode::RegisterMethod(const std::string& methodName, int paramCount)
{
	methods[methodName] = paramCount;
}

void ClassDefinitionNode::RegisterClassMethod(const std::string& methodName, int paramCount)
{
	classMethods[methodName] = paramCount;
}

bool ClassDefinitionNode::HasMethod(const std::string &methodName)
{
	return methods.find(methodName) != methods.end();
}

bool ClassDefinitionNode::HasClassMethod(const std::string &methodName)
{
	return classMethods.find(methodName) != classMethods.end();
}

int ClassDefinitionNode::ParamCountForClassMethod(const std::string &methodName)
{
	return classMethods[methodName];
}

int ClassDefinitionNode::ParamCountForMethod(const std::string &methodName)
{
	return methods[methodName];
}

void ClassDefinitionNode::AppendMethod(MethodAssignmentNode *newMethod)
{
	methodNodes.push_back(newMethod);
}

void ClassDefinitionNode::AppendClassMethod(ClassMethodAssignmentNode *newClassMethod)
{
	classMethodNodes.push_back(newClassMethod);
}

AssemblyBlock *ClassDefinitionNode::GenerateCode()
{
	ASTIterator end(NULL);
	AssemblyBlock *a = new AssemblyBlock;
	AssemblyBlock *fn;
	AssemblyBlock *dispatch = new AssemblyBlock;

	for (MethodIterator i = methodNodes.begin(); i != methodNodes.end(); i++)
	{
		MethodAssignmentNode *m = *i;
		m->GenerateCode();
		fn = m->GetAuxiliaryCode();
		fn->LabelFirstInstruction(GenerateFunctionLabel(m->Name(), name));

		dispatch->cmp(ebx, Dword(goatHash(m->Name())));
		dispatch->je(*new Operand(GenerateFunctionLabel(m->Name(), name)));

		a->AppendBlock(fn);
	}

	for (ClassMethodIterator i = classMethodNodes.begin(); i != classMethodNodes.end(); i++)
	{
		ClassMethodAssignmentNode *c = *i;
		std::string cfnLabel = GenerateClassMethodLabel(c->Name(), name);

		c->GenerateCode();
		fn = c->GetAuxiliaryCode();
		fn->LabelFirstInstruction(cfnLabel);
		fn->PrependItem(new GlobalSymbol(cfnLabel));
		scope->GetSourceFile()->AddGlobalSymbol(cfnLabel);
		a->AppendBlock(fn);
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

std::string GenerateFunctionLabel(const std::string functionName, const std::string className)
{
	std::string fnName = "__" + className + "_" + functionName;
	return SanitizeLabel(fnName);
}

std::string GenerateClassMethodLabel(const std::string functionName, const std::string className)
{
	std::string cfnName = "c_" + className + "_" + functionName;
	return SanitizeLabel(cfnName);
}
