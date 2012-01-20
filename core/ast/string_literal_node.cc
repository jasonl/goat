#include "../goat.h"
#include "../ast_node.h"
#include "../source_file.h"

void StringLiteralNode::Analyse( Scope *_scope ) {
  scope = _scope;
  strLabelName = scope->GetSourceFile()->AddString(contents);
}

AssemblyBlock *StringLiteralNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;

  a->mov(eax, *new Operand(strLabelName));
  a->mov(ecx, Dword(goatHash("String")));
  a->mov(edx, *DispatchOperandFor("String", scope->GetSourceFile()));

  a->CommentLastInstruction("Move String Literal \"" + contents + "\" into eax/ecx/edx");
  return a;
}

AssemblyBlock *StringLiteralNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock;

  a->push( Dword(goatHash("String")) );
  a->push( *DispatchOperandFor("String", scope->GetSourceFile()) );
  a->push( *new Operand(strLabelName));

  a->CommentLastInstruction("Push String Literal \"" + contents + "\" onto stack");
  return a;
}
