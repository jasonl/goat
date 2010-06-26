#ifndef OPERAND_H
#define OPERAND_H

#include <iostream>
#include <stdint.h>

typedef uint32_t Register;

class Operand {
public:
  enum OperandType { 
    Null,
    Direct,
    Indirect,
    Immediate };

  enum OperandSize {
    Byte,
    Word,
    Dword };

  Operand( OperandType );
  Operand( uint32_t, OperandSize ); // For immediate operands
  static Operand& Prototype(const Register);
  Operand& operator[](Operand&) const;
  Operand& operator+(Operand&);
  Operand& operator+(const int32_t);
  Operand& operator-(const int32_t);
  Operand& operator*(const uint8_t);
  bool isPrototype();
  friend std::ostream& operator<<( std::ostream&, const Operand& );
 private:
  OperandType type;
  OperandSize size;
  Register base;
  Register offset;
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

Operand &Byte( unsigned uint8_t );
Operand &Word( unsigned uint16_t );
Operand &Dword( unsigned uint32_t );

#endif
