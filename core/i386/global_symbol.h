#ifndef GLOBAL_SYMBOL_H
#define GLOBAL_SYMBOL_H

#include <string>
#include <iostream>
#include "assembler_item.h"

class GlobalSymbol : public AssemblerItem {
 public:
  GlobalSymbol(std::string);
  void Print(std::ostream&) const;
 private:
  std::string symbol;
};

#endif
