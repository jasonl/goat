typedef signed long offset;

class Variable {
  friend class Scope;
 public:
  Variable( std::string );
  //bool IsGlobal();
  //offset OffsetFromEBP();
 private:
  bool global;
  offset ebpOffset;
  std::string name;
  Variable *next;
};
