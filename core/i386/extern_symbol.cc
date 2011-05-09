#include "extern_symbol.h"

ExternSymbol::ExternSymbol( std::string _symbol) {
  symbol = _symbol;
}

void ExternSymbol::Print( std::ostream& stream ) const{
  stream << "extern " << symbol;
}
