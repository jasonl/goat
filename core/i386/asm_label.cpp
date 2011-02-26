#include "asm_label.h"
#include "operand.h"

AsmLabel::AsmLabel( std::string _name ):
  name(_name) {}

std::string AsmLabel::Name() {
  return name;
}

std::string DispatchLabelNameFor(std::string className) {
  return(className + "_dispatch");
}

Operand *DispatchOperandFor(std::string className) {
  return new Operand(DispatchLabelNameFor(className));
}
