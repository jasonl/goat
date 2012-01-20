#ifndef __EXTERN_SYMBOL_H
#define __EXTERN_SYMBOL_H

#include "assembler_item.h"

class ExternSymbol : public AssemblerItem {
 public:
  ExternSymbol(std::string);
  void Print(std::ostream&) const;
 private:
  std::string symbol;
};

#endif
