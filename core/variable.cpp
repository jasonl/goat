#include <string>
#include "variable.h"

Variable::Variable( std::string name, enum VAR_TYPE _type ) {
  type = _type;
  this->name = name;
  this->global = false;
  this->next = NULL;
}
