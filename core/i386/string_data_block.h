#include "assembler_item.h"

class StringDataBlock : public AssemblerItem {
 public:
  StringDataBlock(std::string, int);
  void Print(std::ostream&) const;
 private:
  int bits;
  std::string contents;
};
