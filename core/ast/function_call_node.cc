#include "../ast_node.h"
#include "../goat.h"
#include "../source_file.h"

extern std::string GenerateClassMethodLabel(const std::string, const std::string);

void FunctionCallNode::Analyse(Scope *_scope) {
  ASTIterator end(NULL);
  scope = _scope;

  // TODO: Reify classes?
  if(dynamic_cast<ClassLiteralNode*>(Receiver())) {
	  // Class Method call
	  type = ClassMethodCall;
  } else if(scope->HasVariable(name)) {
	  // Calling a function object that exists in the local scope
	  type = FunctionObjectCall;
  } else {
	  // Method call to an object, with implicit self if not defined
	  type = MethodCall;

	  if(Receiver() == NULL) {
		  SelfNode *self = new SelfNode();
		  AddReceiver(self);
	  }
  }

  for(ASTIterator i = ChildNodes(); i != end; ++i)
	  i->Analyse( scope );
}

void FunctionCallNode::AddReceiver( ASTNode *_receiver ) {
  // TODO: This should check that there isn't already a receiver
  InsertFirstChild( _receiver );
}

AssemblyBlock *FunctionCallNode::GenerateCode()
{
  AssemblyBlock *a = new AssemblyBlock;
  int paramCount = 0;

  switch(type)
  {
  case ClassMethodCall:
	  paramCount = PushParametersOntoStack(a, true);
	  GenerateClassMethodCall(a);
	  break;

  case FunctionObjectCall:
	  paramCount = PushParametersOntoStack(a, false);
	  GenerateFunctionObjectCall(a);
	  break;

  case MethodCall:
	  paramCount = PushParametersOntoStack(a, true);
	  GenerateMethodCall(a);
	  break;
  }

  // If we've passed any parameters on the stack, release the space on return
  if(paramCount > 0)
	  a->add(esp, *new Operand(paramCount * 12));

  return a;
}

void FunctionCallNode::GenerateClassMethodCall(AssemblyBlock *a)
{
	ClassLiteralNode *classNode = dynamic_cast<ClassLiteralNode*>(Receiver());
	std::string cmLabel = GenerateClassMethodLabel(name, classNode->Name());

	a->call(*new Operand(cmLabel));
}

void FunctionCallNode::GenerateMethodCall(AssemblyBlock *a)
{
	if(Receiver() == NULL) {
		goatFatalError("Null receiver found in FunctionalCall AST-Node inferred to be a method call");
	}

	// Put the receiver (i.e. this ) onto eax/ecx/edx
	a->AppendBlock(Receiver()->GenerateCode());

	a->mov(ebx, Dword(goatHash(name)));
	a->call(edx);
	a->CommentLastInstruction("Function Call: " + name);
}

void FunctionCallNode::GenerateFunctionObjectCall(AssemblyBlock *a)
{
	// TODO: Add run-time check that the object is actually a function
	a->call(scope->GeneratePayloadOperand(name));
}

int FunctionCallNode::PushParametersOntoStack(AssemblyBlock *a, bool skipFirst)
{
	int paramCount = 0;
	ASTIterator i = ChildNodes(), end(NULL);

	if (skipFirst)
		i++; // Ignore the first node, which is the receiver

	// Push the parameters onto the stack
	while(i != end) {
		a->AppendBlock(i->PushOntoStack());
		paramCount++;
		i++;
	}

	return paramCount;
}

// Pushes the value returned by calling the function on to the stack
AssemblyBlock *FunctionCallNode::PushOntoStack()
{
  AssemblyBlock *a = GenerateCode();

  a->push( ecx );   // Type Hash of the object
  a->push( edx );   // Dispatch Fnof the object
  a->push( eax );   // Object payload

  return a;
}
