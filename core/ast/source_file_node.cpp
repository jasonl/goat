#include "../ast_node.h"
#include "../source_file.h"

SourceFileNode::SourceFileNode() : ASTNode( ASTNode::SourceFile ) {
}

void SourceFileNode::Analyse( Scope *_scope ) {
  ASTNode *nextNode;
  ASTIterator end(NULL);

  scope = _scope;

  Token *globalName = new Token(Identifier, "__GLOBAL__");
  globalObject = new ClassDefinitionNode(*globalName);

  InsertFirstChild(globalObject);

  ASTIterator i = ChildNodes();

  while( i != end ) {
    if( i->Type() == MutableAssignment || i->Type() == ImmutableAssignment ) {
      nextNode = i->MoveNodeTo(globalObject);
      i = ASTIterator(nextNode);
    } else {
      i++;
    }
  }

  for(ASTIterator i = ChildNodes(); i != end; i++)
    i->Analyse(scope);

}

AssemblyBlock *SourceFileNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;
  ASTIterator end(NULL);

  a->SetSegment(".text");

  if(!scope->GetSourceFile()->IsLibrary()) {
    // Call __Global__#main to start things
    // Add a "start" label for the linker as an entry point
    a->AppendItem(new GlobalSymbol("start"));

    a->mov(eax, Dword(0));
    a->LabelLastInstruction("start");


    a->mov(ebx, Dword(goatHash("main")));
    a->mov(edx, *new Operand(DispatchLabelNameFor("__GLOBAL__")));
    a->call(edx);
    // Default exit code
    a->push( Dword(0) ); // Return exit code of 0
    a->mov(eax, *new Operand(0x01)); // System call number 1 - exit program
    a->sub(esp, *new Operand(0x04)); // OSX / BSD requires extra space on stack
    a->_int(*new Operand(0x80));  // Make the system call

    a->CommentLastInstruction("Default exit back to system");
  }

  for( ASTIterator i = ChildNodes(); i != end; i++ ) {
    a->AppendBlock( i->GenerateCode() );
  }

  return a;
}
