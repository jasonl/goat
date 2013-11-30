#include "../goat.h"
#include "../source_file.h"
#include "../ast_node.h"
#include "../scope.h"
#include "../lexer.h"

void MethodAssignmentNode::Analyse(Scope *_scope)
{
  scope = _scope;
  firstChild->Analyse(scope);
}

void MethodAssignmentNode::SetRValue(FunctionDefNode* _rValue)
{
  AppendChild( _rValue );
  functionNode = _rValue;
}

void MethodAssignmentNode::GenerateCode(AssemblyBlock* a) const
{
	firstChild->GenerateCode(a);
}
