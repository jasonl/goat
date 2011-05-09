#include <sstream>

#include "asm_label.h"
#include "operand.h"
#include "../source_file.h"
#include "../utf8.h"

AsmLabel::AsmLabel( std::string _name ):
  name(_name) {}

std::string AsmLabel::Name() {
  return name;
}

std::string AsmLabel::SanitizedName() {
  return SanitizeLabel(name);
}

std::string DispatchLabelNameFor(std::string className) {
  return(className + "_dispatch");
}

Operand *DispatchOperandFor(std::string className, SourceFile *sf) {
  std::string dispatchLabelName = DispatchLabelNameFor(className);
  std::string sanitizedLabelName = SanitizeLabel(dispatchLabelName);
  sf->AddExternSymbol(sanitizedLabelName);
  return new Operand(sanitizedLabelName);
}

std::string SanitizeLabel( std::string& _label ) {
  std::string::iterator it = _label.begin();
  std::string::iterator end = _label.end();
  std::stringstream sanitizedLabel;
  uint32_t codePoint;

  while(it != end) {
    codePoint = utf8::next(it, end);
    if((codePoint >= 0x30 && codePoint <= 0x39) || // Numbers
       (codePoint >= 0x41 && codePoint <= 0x7a) || // Letters
       (codePoint == 0x5f)) {                      // Underscore
      sanitizedLabel << (char) codePoint;
    } else {
      sanitizedLabel << 'u' << std::hex << codePoint;
    }
  }

  return sanitizedLabel.str();
}
