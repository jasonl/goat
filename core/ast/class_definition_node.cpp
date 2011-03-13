#include "../ast_node.h"
#include "../lexer.h"

std::string GenerateFunctionLabel( ASTNode*, std::string );

ClassDefinitionNode::ClassDefinitionNode( Token &_token ) : ASTNode( ASTNode::ClassDefinition ) {
  token = &_token;
}

void ClassDefinitionNode::Analyse( Scope *_scope ) {
  ASTIterator end(NULL);

  scope = new Scope( _scope );

  // Add a class variable for every assignment (including functions)
  for( ASTIterator i = ChildNodes(); i != end; i++ ) {
    // This all depends on the knowledge that only MutableAssignment
    // and ImmutableAssignment ASTNodes can be found in a class body

    if( scope->HasVariable( i->Content()) ) {
      // TODO: Add warning of redefinition
    }

    scope->AddClassVariable( i->Content() );
    i->Analyse( scope );
    
  }
}

AssemblyBlock *ClassDefinitionNode::GenerateCode() {
  ASTIterator end(NULL);
  AssemblyBlock *a = new AssemblyBlock;
  AssemblyBlock *fn;
  AssemblyBlock *dispatch = new AssemblyBlock;

  for(ASTIterator i = ChildNodes(); i != end; i++) {
    // As we are guaranteed by the parser to only have AssignmentNodes,
    // we don't generate the actual code for them, but merely use the names
    i->GenerateCode();
    fn = i->GetAuxiliaryCode();
    fn->LabelFirstInstruction(GenerateFunctionLabel( &(*i), this->Content() ));

    dispatch->cmp(ecx, Dword(goatHash(i->Content())));
    dispatch->je(*new Operand(GenerateFunctionLabel( &(*i), this->Content())));

    a->AppendBlock(fn);
  }

  // TODO: Write error code for when a non-existant method is called

  dispatch->LabelFirstInstruction(DispatchLabelNameFor(this->Content())); 
  dispatch->PrependItem(new GlobalSymbol(DispatchLabelNameFor(this->Content())));

  dispatch->AppendBlock(a);
  return dispatch;
}

AssemblyBlock *ClassDefinitionNode::GetAuxiliaryCode() {
  return new AssemblyBlock;
}

std::string GenerateFunctionLabel( ASTNode* assignmentNode, std::string className ) {
  return("__" + assignmentNode->Content() + "_" + className);
}
