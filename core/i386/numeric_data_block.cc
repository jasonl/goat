#include "numeric_data_block.h"

NumericDataBlock::NumericDataBlock( uint32_t _value, int _bits ) {
	type = IMMEDIATE;
	value = _value;
	bits = _bits;
	target = "";
}

NumericDataBlock::NumericDataBlock(std::string _target) {
	type = LABEL;
	value = NULL;
	bits = 32;
	target = _target;
}

void NumericDataBlock::Print(std::ostream& stream) const
{
	if (type == IMMEDIATE) {
		switch(bits) {
		case 8: stream <<  "    db "; break;
		case 16: stream << "    dw "; break;
		case 32: stream << "    dd "; break;
		}

		stream << std::hex << value;
	} else {
		stream << "    dd " << target;
	}
}
