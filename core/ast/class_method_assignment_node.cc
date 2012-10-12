#include "../goat.h"
#include "../ast_node.h"
#include "../scope.h"
#include "../lexer.h"

void ClassMethodAssignmentNode::Analyse(Scope *_scope)
{
  scope = _scope;

  ClassDefinitionNode *enclosingClass = dynamic_cast<ClassDefinitionNode*>(parent);

  if (enclosingClass)
	  enclosingClass->RegisterClassMethod(lValue);


  firstChild->Analyse( scope );
}

void ClassMethodAssignmentNode::SetRValue(ASTNode* _rValue)
{
  AppendChild(_rValue);
}

AssemblyBlock *ClassMethodAssignmentNode::GenerateCode() const
{
  AssemblyBlock *a = firstChild->GenerateCode();

  return a;
}
