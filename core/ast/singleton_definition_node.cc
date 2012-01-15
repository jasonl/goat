#include <string>
#include <map>

#include "../ast_node.h"
#include "../i386/dispatch_function.h"
#include "../i386/function_labels.h"

void SingletonDefinitionNode::Analyse(Scope *_scope)
{
    ASTIterator end(NULL);
    scope = new Scope(_scope);

	for (ASTIterator i = ChildNodes(); i != end; i++) {
		i->Analyse(scope);
	}
}

void SingletonDefinitionNode::AddInstanceVariable(const std::string &name)
{
	classVars[name] = lastVarPosition;
	lastVarPosition++;
}

int SingletonDefinitionNode::InstanceVariablePosition(const std::string &name) const
{
	ClassVarMap::const_iterator ci = classVars.find(name);

	if (ci != classVars.end()) {
		return ci->second;
	} else {
		return -1;
	}
}

AssemblyBlock *SingletonDefinitionNode::GenerateCode()
{
    ASTIterator end(NULL);
    AssemblyBlock *a = new AssemblyBlock;
    AssemblyBlock *fn;
	AssemblyBlock *dispatch = new AssemblyBlock;
    DispatchFunction d;

    for(ASTIterator i = ChildNodes(); i != end; i++) {

        MethodAssignmentNode *m = dynamic_cast<MethodAssignmentNode*>(&(*i));

		if (m) {
			std::string methodLabel = GenerateFunctionLabel(m->Name(), name);

			m->GenerateCode();
			fn = m->GetAuxiliaryCode();
			fn->LabelFirstInstruction(methodLabel);

			d.AddMethod(m->Name(), methodLabel);

            a->AppendBlock(fn);
        }
    }

    dispatch = d.GenerateDispatchAssembly();

	dispatch->AppendBlock(a);
    return dispatch;
}

AssemblyBlock *SingletonDefinitionNode::GetAuxiliaryCode()
{
	return new AssemblyBlock;
}
