#include "asm_label.h"
#include "operand.h"
#include "../source_file.hpp"

AsmLabel::AsmLabel( std::string _name ):
  name(_name) {}

std::string AsmLabel::Name() {
  return name;
}

std::string DispatchLabelNameFor(std::string className) {
  return(className + "_dispatch");
}

Operand *DispatchOperandFor(std::string className, SourceFile *sf) {
  std::string dispatchLabelName = DispatchLabelNameFor(className);
  sf->AddExternSymbol(dispatchLabelName);
  return new Operand(DispatchLabelNameFor(className));
}
