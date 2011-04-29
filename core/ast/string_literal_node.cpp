#include "../ast_node.h"
#include "../source_file.h"

StringLiteralNode::StringLiteralNode( Token &_token ) : ASTNode( ASTNode::StringLiteral ) {
  token = &_token;
}

void StringLiteralNode::Analyse( Scope *_scope ) {
  scope = _scope;
  strLabelName = scope->GetSourceFile()->AddString(Content());
}

AssemblyBlock *StringLiteralNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;

  a->mov(eax, *new Operand(strLabelName));
  a->mov(ecx, Dword(goatHash("String")));
  a->mov(edx, *DispatchOperandFor("String", scope->GetSourceFile()));

  a->CommentLastInstruction("Move String Literal \"" + Content() + "\" into eax/ecx/edx");
  return a;
}

AssemblyBlock *StringLiteralNode::PushOntoStack() {
  AssemblyBlock *a = new AssemblyBlock;

  a->push( Dword(goatHash("String")) );
  a->push( *DispatchOperandFor("String", scope->GetSourceFile()) );
  a->push( *new Operand(strLabelName));

  a->CommentLastInstruction("Push String Literal \"" + Content() + "\" onto stack");
  return a;
}
