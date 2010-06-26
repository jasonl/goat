#include "../ast_node.h"
#include "../lexer.h"

ASTDirectOperandNode::ASTDirectOperandNode( TokenIterator &_token ): 
  OperandNode( ASTNode::DirectOperand ) {
  token = &(*_token);
}

// Generate the operand from the source string. Note, only accepts
// lower case registers - eax not EAX
Operand *ASTDirectOperandNode::GenerateOperand() {
  std::string reg = Content();
  
  if( tolower(reg[0]) == 'e' && reg.length() == 3) {
    if( reg == "eax" ) return &eax;
    if( reg == "ebx" ) return &ebx;
    if( reg == "ecx" ) return &ecx;
    if( reg == "edx" ) return &edx;
    if( reg == "esi" ) return &esi;
    if( reg == "edi" ) return &edi;
    if( reg == "ebp" ) return &ebp;
    if( reg == "esp" ) return &esp;
    // Invalid Register
    return NULL;
  } 

  if( reg.length() == 2 ) {
    if( reg == "ax" ) return &ax;
    if( reg == "bx" ) return &bx;
    if( reg == "cx" ) return &cx;
    if( reg == "dx" ) return &dx;
    if( reg == "si" ) return &si;
    if( reg == "di" ) return &di;
    if( reg == "bp" ) return &bp;
    if( reg == "sp" ) return &sp;

    if( reg == "al" ) return &al;
    if( reg == "ah" ) return &ah;
    if( reg == "bl" ) return &bl;
    if( reg == "bh" ) return &bh;
    if( reg == "cl" ) return &cl;
    if( reg == "ch" ) return &ch;
    if( reg == "dl" ) return &dl;
    if( reg == "dh" ) return &dh;
    // Invalid register
    return NULL;
  }
  
  // Invalid register
  return NULL;
}
