#include "../goat.h"
#include "global_symbol.h"

GlobalSymbol::GlobalSymbol( std::string _symbol ) {
  symbol = _symbol;
}

void GlobalSymbol::Print( std::ostream& stream ) const {
  stream << "global " << symbol;
}
