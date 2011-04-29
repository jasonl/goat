#include "numeric_data_block.h"

NumericDataBlock::NumericDataBlock( uint32_t _value, int _bits ) {
  value = _value;
  bits = _bits;
}

void NumericDataBlock::Print(std::ostream& stream) const {
  switch(bits) {
  case 8: stream <<  "    db "; break;
  case 16: stream << "    dw "; break;
  case 32: stream << "    dd "; break;
  }

  stream << std::hex << value;
}
