#ifndef __SEGMENT_DECLARATION_H
#define __SEGMENT_DECLARATION_H

#include <string>
#include <iostream>
#include "assembler_item.h"

class SegmentDeclaration : public AssemblerItem {
 public:
  SegmentDeclaration( std::string _segment);
  void Print(std::ostream&) const;
 private:
  std::string segment;
};

#endif
