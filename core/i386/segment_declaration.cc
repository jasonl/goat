#include "../goat.h"
#include "segment_declaration.h"

SegmentDeclaration::SegmentDeclaration( std::string _segment ) {
  segment = _segment;
}

void SegmentDeclaration::Print( std::ostream& stream ) const{
  stream << "SEGMENT " << segment;
}
