#include <stdint.h>
#include <iostream>
#include "instructions.h"
#include "operand.h"

// Function Declarations
std::string RegisterName( Register );

// Indirect Memory Operand operator
const Operand _ = Operand( Operand::Null );

// 8-bit GP Registers
Operand &al = Operand::Prototype( AL );
Operand &ah = Operand::Prototype( AH );
Operand &bl = Operand::Prototype( BL );
Operand &bh = Operand::Prototype( BH );
Operand &cl = Operand::Prototype( CL );
Operand &ch = Operand::Prototype( CH );
Operand &dl = Operand::Prototype( DL );
Operand &dh = Operand::Prototype( DH );

// 16-bit GP Registers
Operand &ax = Operand::Prototype( AX );
Operand &bx = Operand::Prototype( BX );
Operand &cx = Operand::Prototype( CX );
Operand &dx = Operand::Prototype( DX );
Operand &sp = Operand::Prototype( SP );
Operand &bp = Operand::Prototype( BP );
Operand &si = Operand::Prototype( SI );
Operand &di = Operand::Prototype( DI );

// 32-bit GP Registers
Operand &eax = Operand::Prototype( EAX );
Operand &ebx = Operand::Prototype( EBX );
Operand &ecx = Operand::Prototype( ECX );
Operand &edx = Operand::Prototype( EDX );
Operand &esp = Operand::Prototype( ESP );
Operand &ebp = Operand::Prototype( EBP );
Operand &esi = Operand::Prototype( ESI );
Operand &edi = Operand::Prototype( EDI );

// Operand - DSL for specifying x86 instruction operands
//
// For register operands, there are a series of global prototype
// operands which can be referred to
//
// Constructor - for non-prototype operands
Operand::Operand( OperandType _type ):
  type( _type ) {
  scale = 0;
  displacement = 0;
  prototype = false;
}

// Immediate Operand Constructor
Operand::Operand( uint32_t _value, OperandSize _size ):
  size(_size), value(_value) {
  type = Immediate;
  prototype = false;
  scale = 0;
  displacement = 0;
  base = 0;
  offset = 0;
}


// Prototype constructor - A prototype operand is one that
// represents registers directly, and indirect operands are
// created from the prototypes using the overloaded operators
// below
Operand& Operand::Prototype(const Register base) {
  Operand &this_op = *new Operand( Direct );
  this_op.prototype = true;
  this_op.base = base;
  return this_op;
}

// This is designed to be used with the special _ constructor
// to allow simulation of the syntax of indirect operands
// 
// This works as a constructor for new Operands generated from
// the prototype register operands, which are left untouched.
//e.g.
// Operand *indirect = _[eax];
// Operand *indirect = _[eax-4];
// Operand *complex = _[eax*8+esp];
Operand& Operand::operator[](Operand &reg) const{

  if(reg.prototype) {
    Operand &this_op = *new Operand( Indirect );
    this_op.base = reg.base;
    return this_op;
  } else {
    Operand &this_op = reg;
    this_op.type = Indirect;
    return this_op;
  }
}

// Offset indirect operand constructor - creates a new Operand
// copied from the nominated Operand, setting the displacement. e.g.
//
// _[eax+54]
// _[esp+12]
Operand& Operand::operator+(const int32_t displacement) {

  if(this->prototype) {
    // We set the operand type to Null here, so we can detect
    // if this is used outside an indirect reference - e.g.
    // Invalid: EAX+4 vs. Valid: _[EAX+4]
    Operand &this_op = *new Operand( Null );
    this_op.displacement = displacement;
    this_op.scale = this->scale;
    this_op.offset = this->offset;
    this_op.base = this->base;
    return this_op;
  } else {
    Operand &this_op = *this;  
    this_op.displacement = displacement;
    return this_op;
  }
}

// Offset indirect operand constructor - creates a new Operand
// copied from the nominated Operand, setting the displacement. e.g.
//
// _[eax-54]
// _[esp-12]
Operand& Operand::operator-(const int32_t displacement) {

  if(this->prototype) {
    Operand &this_op = *new Operand( Null );
    this_op.base = this->base;
    this_op.scale = this->scale;
    this_op.displacement = -1 * displacement;
    return this_op;
  } else {
    Operand &this_op = *this;
    this_op.displacement = -1 * displacement;
    return this_op;
  }
}

// Offset indirect operand constructor - creates a new Operand
// (if required) setting the base and offset registers
//
// N.B. This is not commutative - it always acts in the form of
// [base + offset] or [base + offset * scale] or
// [base + offset + disp]. Using forms such as 
// [offset * scale + base] will not work, despite being able to
// be correctly represented as a SIB byte. 
Operand& Operand::operator+( Operand &offset ) {
  
  if( offset.prototype ) {
    Operand &this_op = *new Operand( Null );
    this_op.offset = offset.base;
    this_op.displacement = offset.displacement;
    this_op.scale = offset.scale;
    this_op.base = this->base;
    return this_op;
  } else {
    Operand &this_op = offset;
    this_op.offset = offset.offset;
    this_op.base = this->base;
    return this_op;
  }
}

// Scaled offset operand constructor - creates a new Operand
// (if required), setting the scale for the SIB byte.
//
// _[EBP+EAX*8]
// _[EBP+EAX*8+3]
//
Operand& Operand::operator*(const uint8_t scale_b) {
  //if(!(scale==1 || scale==2 || scale==4 || scale==8)) {
    // Throw an exception
  //}

  if(this->prototype) {
    Operand &this_op = *new Operand( Null );
    this_op.offset = this->base;
    this_op.scale = scale_b;
    return this_op;
  } else {
    Operand &this_op = *this;
    this_op.scale = scale_b;
    return this_op;
  }

}

bool Operand::isPrototype() {
  return prototype;
}

// Helper methods for creating specific sized immediate operands
Operand &Byte( uint8_t _value ) {
  return *new Operand( _value, Operand::Byte );
}

Operand &Word( uint16_t _value ) {
  return *new Operand( _value, Operand::Byte );
}

Operand &Dword( uint32_t _value ) {
  return *new Operand( _value, Operand::Byte );
}

// Stream helper for outputting the assembly code
std::ostream &operator<<(std::ostream& stream, const Operand& op) {
  switch( op.type ) {
  case Operand::Direct:
    stream << RegisterName( op.base );
    break;
  default:
    stream << "NYI"; // Not Yet Implemented!
  }
  return stream;
}

std::string RegisterName( const Register reg ) {
  switch( reg ) {
  case EAX: return "eax";
  case EBX: return "ebx";
  case ECX: return "ecx";
  case EDX: return "edx";
  case ESI: return "esi";
  case EDI: return "edi";
  case ESP: return "esp";
  case EBP: return "ebp";
  case AX: return "ax";
  case BX: return "bx";
  case CX: return "cx";
  case DX: return "dx";
  case SI: return "si";
  case DI: return "di";
  case SP: return "sp";
  case BP: return "bp";
  case AL: return "al";
  case AH: return "ah";
  case BL: return "bl";
  case BH: return "bh";
  case CL: return "cl";
  case CH: return "ch";
  case DL: return "dl";
  case DH: return "dh";
  default: return "xxx";
  }
}
