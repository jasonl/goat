#include "../goat.h"
#include "../ast_node.h"
#include "../source_file.h"
#include "../build_set.h"

void SourceFileNode::Analyse( Scope *_scope ) {
  ASTNode *nextNode;
  ASTIterator end(NULL);

  scope = _scope;

  if(!scope->GetSourceFile()->IsLibrary()) {
    globalObject = new ClassDefinitionNode("__GLOBAL__");

    InsertFirstChild(globalObject);

    ASTIterator i = ChildNodes();

    while( i != end ) {
		if(i->IsRelocatedToGlobalObject()) {
			nextNode = i->MoveNodeTo(globalObject);
			// We need to change ConstantAssignments to MethodAssignments
			ConstantAssignmentNode *c = dynamic_cast<ConstantAssignmentNode*>(&(*i));

			if (c) {
				MethodAssignmentNode *m = new MethodAssignmentNode(c->VariableName());

				ASTIterator j = i->ChildNodes();

				if (j != end) {
					m->SetFirstChild(&(*j));
					i->SetFirstChild(NULL);
				}

				while(j != end) {
					j->SetParent(m);
					j++;
				}

				globalObject->ReplaceChild(&(*i), m);
			}

			i = ASTIterator(nextNode);
		} else {
			i++;
		}
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

	// Call new on all Singletons
	BuildSet *bs = scope->GetSourceFile()->GetBuildSet();
	Namespace::iterator end = bs->LastSingleton();

	for (Namespace::iterator i = bs->FirstSingleton(); i != end; i++) {
		a->mov(ebx, Dword(goatHash("new")));
		a->call(*new Operand("__" + (*i) + "_dispatch"));
	}

	// Call main on the global object as the entry point.
    a->mov(ebx, Dword(goatHash("main")));
    a->mov(edx, *new Operand(DispatchLabelNameFor("__GLOBAL__")));
    a->call(edx);

    // Default exit code, executed after returning from main.
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
