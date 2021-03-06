#include "../goat.h"
#include "../ast_node.h"

// Generate the operand from the source string. Note, only accepts
// lower case registers - eax not EAX
Operand *DirectOperandNode::GenerateOperand() const
{
  if( tolower(reg[0]) == 'e' && reg.length() == 3) {
    if( reg == "eax" ) return &eax;
    if( reg == "ebx" ) return &ebx;
    if( reg == "ecx" ) return &ecx;
    if( reg == "edx" ) return &edx;
    if( reg == "esi" ) return &esi;
    if( reg == "edi" ) return &edi;
    if( reg == "ebp" ) return &ebp;
    if( reg == "esp" ) return &esp;
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
  }

  // Assume its a label
  Operand *op = new Operand(reg);
  op->SetSize(size);
  return op;
}
