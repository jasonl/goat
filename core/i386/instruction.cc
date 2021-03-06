#include "../goat.h"
#include "instruction.h"

Instruction::Instruction( std::string _mnemonic ) {
  mnemonic = _mnemonic;
  operand1 = 0;
  operand2 = 0;
  operand3 = 0;
}

Instruction::Instruction( std::string _mnemonic, Operand *op1 ) {
  mnemonic = _mnemonic;
  operand1 = op1;
  operand2 = NULL;
  operand3 = NULL;
}

Instruction::Instruction( std::string _mnemonic,  Operand *op1,
			  Operand *op2 ) {
  mnemonic = _mnemonic;
  operand1 = op1;
  operand2 = op2;
  operand3 = NULL;
}

Instruction::Instruction( std::string _mnemonic, Operand* op1,
			  Operand* op2, Operand* op3 ) {
  mnemonic = _mnemonic;
  operand1 = op1;
  operand2 = op2;
  operand3 = op3;
}

void Instruction::Print( std::ostream& stream ) const {
  stream << "    " << mnemonic;
  if( operand1 ) stream << " " << *operand1;
  if( operand2 ) stream << ", " << *operand2;
  if( operand3 ) stream << ", " << *operand3;
}

Instruction::~Instruction() {
  if (operand1->isPrototype()) delete operand1;
  if (operand2->isPrototype()) delete operand2;
  if (operand3->isPrototype()) delete operand3;
}
