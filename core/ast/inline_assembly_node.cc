#include "../goat.h"
#include "../ast_node.h"

void InlineAssemblyNode::Analyse( Scope *_scope) {
  ASTIterator end(NULL);

  scope = _scope;

  for(ASTIterator i = ChildNodes(); i != end; i++) {
    i->Analyse( scope );
  }
}

void InlineAssemblyNode::GenerateCode(AssemblyBlock* a) const 
{
	ASTIterator end(NULL);

	for (ASTIterator i = ChildNodes(); i != end; i++) {
		i->GenerateCode(a);
	}
}
