#include "assembler_item.h"

class NumericDataBlock : public AssemblerItem {
 public:
  NumericDataBlock(uint32_t, int);
  void Print(std::ostream&) const;
 private:
  int bits;
  uint32_t value;
};
