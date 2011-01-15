#include "../ast_node.h"

SourceFileNode::SourceFileNode() : ASTNode( ASTNode::SourceFile ) {
}

void SourceFileNode::Analyse( Scope *scope ) {
  ASTIterator end(NULL);

  for( ASTIterator i = ChildNodes(); i != end; i++ ) {
    i->Analyse( scope );
  } 
}

AssemblyBlock *SourceFileNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;
  ASTIterator end(NULL);

  a->SetSegment(".text");

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
