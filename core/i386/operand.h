#ifndef OPERAND_H
#define OPERAND_H

typedef enum _operand_type {
  Null,
  Register,
  Memory,
  Immediate
} operand_type;

typedef uint32_t register_t;

class Operand {
public:
  Operand( operand_type );
  static Operand& Prototype(const register_t);
  Operand& operator[](Operand&) const;
  Operand& operator+(Operand&);
  Operand& operator+(const int32_t);
  Operand& operator-(const int32_t);
  Operand& operator*(const uint8_t);
  //private:
  operand_type type;
  register_t base;
  register_t offset;
  uint32_t value;
  int32_t displacement;
  // The scale is either 1, 2, 4 or 8, and is the value the offset
  // register is multiplied by.
  uint8_t scale;
  // A prototype Operand is one which can only be copied, not modified
  // e.g. the const Operands used for registers
  bool prototype;
};

// Prototype operands
// NB. We can't declare these as const, because we can't know at compile
// time that the this pointer in the Operand::operator methods will never
// point to these.
extern Operand &al, &ah, &bl, &bh, &cl, &ch, &dl, &dh;
extern Operand &ax, &bx, &cx, &dx, &sp, &bp, &di, &si;
extern Operand &eax, &ebx, &ecx, &edx, &esp, &ebp, &esi, &edi;
extern const Operand _;
#endif
