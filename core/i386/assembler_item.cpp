#include "assembler_item.h"

std::ostream& operator<<( std::ostream &_stream, const AssemblerItem& ai ) {
  if( ai.label ) {
    _stream << ai.label->Name() << ":\n";
  }

  ai.Print( _stream );

  if(ai.comment.length() > 0) _stream << "\t\t\t\t;" << ai.comment;

  return _stream;
}
