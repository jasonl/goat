#include <string>
#include <map>

#include "../ast_node.h"   // For goatHash

#include "assembly_block.h"
#include "dispatch_function.h"

void DispatchFunction::AddMethod(std::string methodName, std::string asmLabel)
{
	methods.insert(std::pair<std::string,std::string>(methodName, asmLabel));
}

AssemblyBlock *DispatchFunction::GenerateDispatchAssembly() const
{
	AssemblyBlock *dispatch = new AssemblyBlock;

	for (DispatchMapIterator i = methods.begin(); i != methods.end(); i++) {
		dispatch->cmp(ebx, Dword(goatHash((*i).first)));
		dispatch->je(*new Operand((*i).second));
	}

	dispatch->push(Dword(5));
	dispatch->mov(eax, *new Operand(0x01));
	dispatch->sub(esp, *new Operand(0x04));
	dispatch->_int(*new Operand(0x80));

	dispatch->CommentLastInstruction("Exit with code 5 if not found");

	return dispatch;
}
