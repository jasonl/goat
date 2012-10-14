#include "../goat.h"
#include "../ast_node.h"
#include "../scope.h"
#include "../lexer.h"

void ClassMethodAssignmentNode::Analyse(Scope *_scope)
{
  scope = _scope;
  firstChild->Analyse( scope );
}

void ClassMethodAssignmentNode::SetRValue(FunctionDefNode* _rValue)
{
  AppendChild(_rValue);
  functionNode = _rValue;
}

AssemblyBlock *ClassMethodAssignmentNode::GenerateCode() const
{
  AssemblyBlock *a = firstChild->GenerateCode();

  return a;
}
