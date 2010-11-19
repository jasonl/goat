#include "instruction.h"

Instruction::Instruction( std::string _mnemonic ) {
  mnemonic = _mnemonic;
  operand1 = 0;
  operand2 = 0;
  operand3 = 0;
  next = NULL;
  label = NULL;
}

Instruction::Instruction( std::string _mnemonic, Operand *op1 ) {
  mnemonic = _mnemonic;
  operand1 = op1;
  operand2 = NULL;
  operand3 = NULL;
  next = NULL;
  label = NULL;
}

Instruction::Instruction( std::string _mnemonic,  Operand *op1,
			  Operand *op2 ) {
  mnemonic = _mnemonic;
  operand1 = op1;
  operand2 = op2;
  operand3 = NULL;
  next = NULL;
  label = NULL;
}

Instruction::Instruction( std::string _mnemonic, Operand* op1, 
			  Operand* op2, Operand* op3 ) {
  mnemonic = _mnemonic;
  operand1 = op1;
  operand2 = op2;
  operand3 = op3;
  next = NULL;
  label = NULL;
}

void Instruction::SetLabel( std::string _label ) {
  label = new AsmLabel( _label );
}

void Instruction::SetComment( std::string _comment ) {
  comment = _comment;
}

std::ostream& operator<<( std::ostream &stream, const Instruction &ins ) {
  if( ins.label ) {
    stream << ins.label->Name() << ":\n";
  }

  stream << "    " << ins.mnemonic;
  if( ins.operand1 ) stream << " " << *ins.operand1;
  if( ins.operand2 ) stream << ", " << *ins.operand2;
  if( ins.operand3 ) stream << ", " << *ins.operand3;
  if( ins.comment.length() > 0 ) stream << "\t\t\t\t; " << ins.comment;
  return stream;
} 

Instruction::~Instruction() {
  if (operand1->isPrototype()) delete operand1;
  if (operand2->isPrototype()) delete operand2;
  if (operand3->isPrototype()) delete operand3;
  if (label) delete label;
}
