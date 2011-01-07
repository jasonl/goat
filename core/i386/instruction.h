#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include "assembler_item.h"
#include "operand.h"

class Instruction : public AssemblerItem{
 public:
  Instruction(std::string);
  Instruction(std::string, Operand* );
  Instruction(std::string, Operand*, Operand*);
  Instruction(std::string, Operand*, Operand*, Operand*);
  void Print( std::ostream& ) const;
  ~Instruction();
 private:
  std::string mnemonic;
  Operand *operand1;
  Operand *operand2;
  Operand *operand3;
};

#endif
