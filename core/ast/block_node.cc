#include "../goat.h"
#include "../ast_node.h"

/*
 * BlockNode
 *
 * AST-Node represeting a block, which is simply a group of statements.
 * Note that a block does not create a new lexical scope
 *
 */

void BlockNode::Analyse( Scope *_scope)
{
  ASTIterator end(NULL);

  scope = _scope;

  for(ASTIterator i = ChildNodes(); i != end; i++)
  {
    i->Analyse( scope );
  }
}

void BlockNode::GenerateCode(AssemblyBlock* a) const
{
    ASTIterator end(NULL);

    for(ASTIterator i = ChildNodes(); i != end; i++) {
	i->GenerateCode(a);
    }
}
