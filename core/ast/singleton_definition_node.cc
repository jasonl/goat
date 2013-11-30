#include "../goat.h"
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

void SingletonDefinitionNode::GenerateCode(AssemblyBlock* a) const
{
    ASTIterator end(NULL);
    AssemblyBlock *functions = new AssemblyBlock;
    AssemblyBlock *dispatch = new AssemblyBlock;
    DispatchFunction d;

    for (ASTIterator i = ChildNodes(); i != end; i++) {
	    MethodAssignmentNode *m = dynamic_cast<MethodAssignmentNode*>(&(*i));

	    if (m) {
		    AssemblyBlock *fn = new AssemblyBlock;
		    std::string methodLabel = GenerateFunctionLabel(m->Name(), name);
		    m->GetAuxiliaryCode(fn);
		    fn->LabelFirstInstruction(methodLabel);
		    d.AddMethod(m->Name(), methodLabel);
		    functions->AppendBlock(fn); // Implicit delete
	    }
    }

    d.GenerateDispatchAssembly(a);

    std::string dispatchLabel = DispatchLabelNameFor(name);

    dispatch->LabelFirstInstruction(dispatchLabel);
    dispatch->PrependItem(new GlobalSymbol(dispatchLabel));
    scope->GetSourceFile()->AddGlobalSymbol(dispatchLabel);

    a->AppendBlock(dispatch); // Implcit delete
    a->AppendBlock(functions); // Implicit delete
}

void SingletonDefinitionNode::GetAuxiliaryCode(AssemblyBlock* a) const
{
	AssemblyBlock *b = new AssemblyBlock;
	a->SetSegment(".data");

	for (uint32_t i = 0; i < classVars.size(); i++) {
		b->dw(0);
		b->dw("Null_dispatch");
		b->dw(goatHash("Null"));
	}

	b->LabelFirstInstruction(PayloadLabelName());
	a->AppendBlock(b);

	a->SetSegment(".text");
}
