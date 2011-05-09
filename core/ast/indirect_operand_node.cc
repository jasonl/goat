#include "../ast_node.h"

Operand *IndirectOperandNode::GenerateOperand() const
{
  OperandIterator end(NULL);
  Operand *base = NULL; // Temporary value for reference

  if( reg[0] == 'e' && reg.length() == 3) {
    if( reg == "eax" ) base = &eax;
    if( reg == "ebx" ) base = &ebx;
    if( reg == "ecx" ) base = &ecx;
    if( reg == "edx" ) base = &edx;
    if( reg == "esi" ) base = &esi;
    if( reg == "edi" ) base = &edi;
    if( reg == "ebp" ) base = &ebp;
    if( reg == "esp" ) base = &esp;
    // Invalid Register
    return NULL;
  }

  if( reg.length() == 2 ) {
    if( reg == "ax" ) base = &ax;
    if( reg == "bx" ) base = &bx;
    if( reg == "cx" ) base = &cx;
    if( reg == "dx" ) base = &dx;
    if( reg == "si" ) base = &si;
    if( reg == "di" ) base = &di;
    if( reg == "bp" ) base = &bp;
    if( reg == "sp" ) base = &sp;

    if( reg == "al" ) base = &al;
    if( reg == "ah" ) base = &ah;
    if( reg == "bl" ) base = &bl;
    if( reg == "bh" ) base = &bh;
    if( reg == "cl" ) base = &cl;
    if( reg == "ch" ) base = &ch;
    if( reg == "dl" ) base = &dl;
    if( reg == "dh" ) base = &dh;
    // Invalid register
    return NULL;
  }

  // TODO: Generate correct offsets etc from terms

  return &_[*base];
}

