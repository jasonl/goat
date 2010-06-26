#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include <string>
#include <iostream>
#include "operand.h"


class AsmLabel;

class Instruction {
  friend class AssemblyBlock;
  friend class InstructionIterator;
public:
  Instruction(std::string);
  Instruction(std::string, Operand* );
  Instruction(std::string, Operand*, Operand*);
  Instruction(std::string, Operand*, Operand*, Operand*);
  friend std::ostream& operator<<( std::ostream&, const Instruction&);
  ~Instruction();
private:
  AsmLabel *label;
  std::string mnemonic;
  Operand *operand1;
  Operand *operand2;
  Operand *operand3;
  Instruction *next;
};

class InstructionIterator {
  Instruction *p;
public:
  InstructionIterator( Instruction* start) : p(start) {}
  InstructionIterator( const InstructionIterator& asti ) : p(asti.p) {}
  InstructionIterator operator++() {p = p->next; return *this;}
  InstructionIterator operator++(int) { p = p->next; return *this;}
  bool operator==( const InstructionIterator& asti ) { return asti.p == p; }
  bool operator!=( const InstructionIterator& asti ) { return asti.p != p; }
  Instruction& operator*() { return *p; }
  Instruction* operator->() { return p; }
};

#endif
