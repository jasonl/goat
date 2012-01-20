#include "../goat.h"
#include "../ast_node.h"

void ParameterDefNode::Analyse( Scope *_scope ) {
  scope = _scope;

  if( scope->HasParameterVariable(name)) {
    // TODO: Error! Duplicate Parameter Name
  } else {
    scope->AddParameterVariable(name);
  }
}
