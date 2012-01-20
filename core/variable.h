#ifndef __VARIABLE_H
#define __VARIABLE_H

typedef signed long offset;

class Variable {
  friend class Scope;
 public:
  enum VAR_TYPE {
    Local, Parameter
  };

  Variable( std::string, enum VAR_TYPE );
  enum VAR_TYPE Type() { return type; }
 private:
  enum VAR_TYPE type;
  bool global;
  offset ebpOffset;
  std::string name;
  Variable *next;
};

#endif
