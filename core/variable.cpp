#include <string>
#include "variable.h"

Variable::Variable( std::string name ) {
  this->name = name;
  this->global = false;
  this->next = NULL;
}
