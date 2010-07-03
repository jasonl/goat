#ifndef __ASM_LABEL_H
#define __ASM_LABEL_H

#include <string>

class AsmLabel {
 public:
  AsmLabel( std::string );
 private:
  std::string name;
};

#endif
