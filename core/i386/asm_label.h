#ifndef __ASM_LABEL_H
#define __ASM_LABEL_H

#include <string>

class SourceFile;
class Operand;

class AsmLabel {
 public:
  AsmLabel( std::string );
  std::string Name();
 private:
  std::string name;
};

std::string DispatchLabelNameFor(std::string);
Operand *DispatchOperandFor(std::string, SourceFile*);

#endif
