#include <string>
#include "operand.h"

using namespace std;

class Label {

};

class Instruction {
  Instruction(string);
  Instruction(string, Operand& );
  Instruction(string, Operand&, Operand&);
  Instruction(string, Operand&, Operand&, Operand&);
  ~Instruction();
private:
  Label *label;
  string mnemonic;
  Operand *operand1;
  Operand *operand2;
  Operand *operand3;
};

Instruction::Instruction( string _mnemonic ) {
  mnemonic = _mnemonic;
  operand1 = 0;
  operand2 = 0;
  operand3 = 0;
}

Instruction::Instruction( string _mnemonic, Operand& op1 ) {
  mnemonic = _mnemonic;
  operand1 = &op1;
  operand2 = 0;
  operand3 = 0;
}

Instruction::Instruction( string _mnemonic,  Operand& op1,
			  Operand& op2 ) {
  mnemonic = _mnemonic;
  operand1 = &op1;
  operand2 = &op2;
  operand3 = 0;
}

Instruction::Instruction( string _mnemonic, Operand& op1, 
			  Operand& op2, Operand& op3 ) {
  mnemonic = _mnemonic;
  operand1 = &op1;
  operand2 = &op2;
  operand3 = &op3;
}

Instruction::~Instruction() {
  if (operand1->isPrototype()) delete operand1;
  if (operand2->isPrototype()) delete operand2;
  if (operand3->isPrototype()) delete operand3;
}
