#ifndef __ASM_LABEL_H
#define __ASM_LABEL_H

class Operand;
class SourceFile;

class AsmLabel {
 public:
  AsmLabel( std::string );
  std::string Name();
  std::string SanitizedName();
 private:
  std::string name;
};

std::string DispatchLabelNameFor(std::string);
Operand *DispatchOperandFor(std::string, SourceFile*);
std::string SanitizeLabel(std::string&);
#endif
