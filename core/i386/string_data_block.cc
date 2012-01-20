#include "../goat.h"
#include "string_data_block.h"

StringDataBlock::StringDataBlock( std::string _contents, int _bits ) {
  contents = _contents;
  bits = _bits;
}

void StringDataBlock::Print(std::ostream& stream) const {
  switch(bits) {
  case 8: stream <<  "    db "; break;
  case 16: stream << "    dw "; break;
  case 32: stream << "    dd "; break;
  }

  stream << "\"" << contents << "\"";
}
