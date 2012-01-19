#include "assembler_item.h"

class NumericDataBlock : public AssemblerItem
{
  public:
	NumericDataBlock(uint32_t, int);
	NumericDataBlock(std::string);
	void Print(std::ostream&) const;
  private:
	int bits;
	uint32_t value;
	std::string target;
	enum { IMMEDIATE, LABEL } type;
};
