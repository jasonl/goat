#include "../ast_node.h"
#include "../source_file.h"

extern std::string GenerateClassMethodLabel(const std::string, const std::string);

void FunctionCallNode::Analyse(Scope *_scope) {
  ASTIterator end(NULL);
  scope = _scope;

  // Add the implicit self receiver if it doesn't exist
  if( Receiver() == NULL ) {
    SelfNode *self = new SelfNode();
    AddReceiver( self );
  }


  for( ASTIterator i = ChildNodes(); i != end; ++i ) {
    i->Analyse( scope );
  }
}

void FunctionCallNode::AddReceiver( ASTNode *_receiver ) {
  // TODO: This should check that there isn't already a receiver
  InsertFirstChild( _receiver );
}

AssemblyBlock *FunctionCallNode::GenerateCode()
{
  AssemblyBlock *a = new AssemblyBlock;
  ASTIterator end(NULL);
  uint32_t paramCount = 0;

  ASTIterator i = ChildNodes();
  i++; // Ignore the first node, which is the receiver

  // Push the parameters onto the stack
  while(i != end) {
      a->AppendBlock(i->PushOntoStack());
      paramCount++;
	  i++;
  }

  // Determine if we're making a normal method call or a class method call
  // TODO: Reify classes?
  ClassLiteralNode *classNode = dynamic_cast<ClassLiteralNode*>(Receiver());

  if(classNode)
  {
      std::string cmLabel = GenerateClassMethodLabel(name, classNode->Name());
      a->call(*new Operand(cmLabel));
  } else {
	// Put the receiver (i.e. this ) onto eax/ecx/edx
	a->AppendBlock( Receiver()->GenerateCode() );

	a->mov( ebx, Dword(goatHash(name)));
	a->call( edx );
	a->CommentLastInstruction( "Function Call: " + name );
  }

  // If we've passed any parameters on the stack, release the space on return
  if(paramCount > 0) {
    a->add(esp, *new Operand(paramCount * 12));
	}
  return a;
}

AssemblyBlock *FunctionCallNode::PushOntoStack()
{
  AssemblyBlock *a = GenerateCode();

  a->push( ecx );   // Type Hash of the object
  a->push( edx );   // Dispatch Fnof the object
  a->push( eax );   // Object payload

  return a;
}
