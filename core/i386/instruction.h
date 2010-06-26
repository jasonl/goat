#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include <string>
#include "operand.h"

class AsmLabel;

class Instruction {
  friend class AssemblyBlock;
public:
  Instruction(std::string);
  Instruction(std::string, Operand* );
  Instruction(std::string, Operand*, Operand*);
  Instruction(std::string, Operand*, Operand*, Operand*);
  ~Instruction();
private:
  AsmLabel *label;
  std::string mnemonic;
  Operand *operand1;
  Operand *operand2;
  Operand *operand3;
  Instruction *next;
};

#endif
