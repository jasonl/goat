#include "../ast_node.h"

SourceFileNode::SourceFileNode() : ASTNode( ASTNode::SourceFile ) {
}

void SourceFileNode::Analyse( Scope *scope ) {
  ASTNode *nextNode;
  ASTIterator end(NULL);

  Token *globalName = new Token(Identifier, "__GLOBAL__");
  globalObject = new ASTClassDefinitionNode(*globalName);

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

  // Call __Global__#main to start things
  a->mov(ecx, Dword(goatHash("main")));
  a->mov(edx, *new Operand("__GLOBAL___dispatch")); 
  a->call(edx);

  for( ASTIterator i = ChildNodes(); i != end; i++ ) {
    a->AppendBlock( i->GenerateCode() );
  }

  // Default exit code
  a->push( Dword(0) ); // Return exit code of 0
  a->mov(eax, *new Operand(0x01)); // System call number 1 - exit program
  a->sub(esp, *new Operand(0x04)); // OSX / BSD requires extra space on stack
  a->_int(*new Operand(0x80));  // Make the system call
  
  a->CommentLastInstruction("Default exit back to system");

  return a;
}
