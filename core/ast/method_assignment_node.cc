#include "../goat.h"
#include "../source_file.h"
#include "../ast_node.h"
#include "../scope.h"
#include "../lexer.h"

void MethodAssignmentNode::Analyse(Scope *_scope)
{
  scope = _scope;

  ClassDefinitionNode *enclosingClass = dynamic_cast<ClassDefinitionNode*>(parent);

  if (enclosingClass)
	  enclosingClass->RegisterMethod(lValue);

  firstChild->Analyse(scope);
}

void MethodAssignmentNode::SetRValue(ASTNode* _rValue)
{
  AppendChild( _rValue );
}

AssemblyBlock *MethodAssignmentNode::GenerateCode() const
{
  AssemblyBlock *a = firstChild->GenerateCode();

  return a;
}
