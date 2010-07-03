#include "asm_label.h"

AsmLabel::AsmLabel( std::string _name ):
  name(_name) {}

std::string AsmLabel::Name() {
  return name;
}
