#include "operand.h"
#include "instruction.h"
#include "assembly_block.h"

void AssemblyBlock::AAA() {
  this->push_back( new Instruction("AAA") );
}

void AssemblyBlock::AAD() {
  this->push_back( new Instruction("AAD") );
}

void AssemblyBlock::AAM() {
  this->push_back( new Instruction("AAM") );
}

void AssemblyBlock::AAS() {
  this->push_back( new Instruction("AAS") );
}

void AssemblyBlock::ADC( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("ADC", op1, op2) );
}

void AssemblyBlock::ADD( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("ADD", op1, op2) );
}

void AssemblyBlock::AND( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("AND", op1, op2) );
}

void AssemblyBlock::ARPL( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("ARPL", op1, op2) );
}

void AssemblyBlock::BOUND( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("BOUND", op1, op2) );
}

void AssemblyBlock::BSF( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("BSF", op1, op2) );
}

void AssemblyBlock::BSR( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("BSR", op1, op2) );
}

void AssemblyBlock::BSWAP( Operand &op1 ) {
  this->push_back( new Instruction("BSWAP", op1) );
}

void AssemblyBlock::BT( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("BT", op1, op2) );
}

void AssemblyBlock::BTC( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("BTC", op1, op2) );
}

void AssemblyBlock::BTR( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("BTR", op1, op2) );
}

void AssemblyBlock::BTS( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("BTS", op1, op2) );
}

void AssemblyBlock::CALL( Operand &op1 ) {
  this->push_back( new Instruction("CALL", op1) );
}

void AssemblyBlock::CALL_FAR( Operand &op1 ) {
  this->push_back( new Instruction("CALL_FAR", op1) );
}

void AssemblyBlock::CBW() {
  this->push_back( new Instruction("CBW") );
}

void AssemblyBlock::CWD() {
  this->push_back( new Instruction("CWD") );
}

void AssemblyBlock::CDW() {
  this->push_back( new Instruction("CDW") );
}

void AssemblyBlock::CWDE() {
  this->push_back( new Instruction("CWDE") );
}

void AssemblyBlock::CLC() {
  this->push_back( new Instruction("CLC") );
}

void AssemblyBlock::CLD() {
  this->push_back( new Instruction("CLD") );
}

void AssemblyBlock::CLI() {
  this->push_back( new Instruction("CLI") );
}

void AssemblyBlock::CLTS() {
  this->push_back( new Instruction("CLTS") );
}

void AssemblyBlock::CMC() {
  this->push_back( new Instruction("CMC") );
}

void AssemblyBlock::CMP( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("CMP", op1, op2) );
}

void AssemblyBlock::CMPSB() {
  this->push_back( new Instruction("CMPSB") );
}

void AssemblyBlock::CMPSW() {
  this->push_back( new Instruction("CMPSW") );
}

void AssemblyBlock::CMPSD() {
  this->push_back( new Instruction("CMPSD") );
}

void AssemblyBlock::DAA() {
  this->push_back( new Instruction("DAA") );
}

void AssemblyBlock::DAS() {
  this->push_back( new Instruction("DAS") );
}

void AssemblyBlock::DEC( Operand &op1 ) {
  this->push_back( new Instruction("DEC", op1) );
}

void AssemblyBlock::DIV( Operand &op1 ) {
  this->push_back( new Instruction("DIV", op1) );
}

void AssemblyBlock::ENTER( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("ENTER", op1, op2) );
}

void AssemblyBlock::HLT() {
  this->push_back( new Instruction("HLT") );
}

void AssemblyBlock::IDIV( Operand &op1 ) {
  this->push_back( new Instruction("IDIV", op1) );
}

void AssemblyBlock::IMUL( Operand &op1 ) {
  this->push_back( new Instruction("IMUL", op1) );
}

void AssemblyBlock::IMUL( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("IMUL", op1, op2) );
}

void AssemblyBlock::IMUL( Operand &op1, Operand &op2, Operand &op3 ) {
  this->push_back( new Instruction("IMUL", op1, op2, op3) );
}

void AssemblyBlock::IN( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("IN", op1, op2) );
}

void AssemblyBlock::INC( Operand &op1 ) {
  this->push_back( new Instruction("INC", op1) );
}

void AssemblyBlock::INSB() {
  this->push_back( new Instruction("INSB") );
}

void AssemblyBlock::INSW() {
  this->push_back( new Instruction("INSW") );
}

void AssemblyBlock::INSD() {
  this->push_back( new Instruction("INSD") );
}

void AssemblyBlock::INT( Operand &op1 ) {
  this->push_back( new Instruction("INT", op1) );
}

void AssemblyBlock::INT3() {
  this->push_back( new Instruction("INT3") );
}

void AssemblyBlock::INTO() {
  this->push_back( new Instruction("INTO") );
}

void AssemblyBlock::INVTLB( Operand &op1 ) {
  this->push_back( new Instruction("INVTLB", op1) );
}

void AssemblyBlock::IRET() {
  this->push_back( new Instruction("IRET") );
}

void AssemblyBlock::IRETW() {
  this->push_back( new Instruction("IRETW") );
}

void AssemblyBlock::IRETD() {
  this->push_back( new Instruction("IRETD") );
}

void AssemblyBlock::JA( Operand &op1 ) {
  this->push_back( new Instruction("JA", op1) );
}

void AssemblyBlock::JAE( Operand &op1 ) {
  this->push_back( new Instruction("JAE", op1) );
}

void AssemblyBlock::JB( Operand &op1 ) {
  this->push_back( new Instruction("JB", op1) );
}

void AssemblyBlock::JBE( Operand &op1 ) {
  this->push_back( new Instruction("JBE", op1) );
}

void AssemblyBlock::JC( Operand &op1 ) {
  this->push_back( new Instruction("JC", op1) );
}

void AssemblyBlock::JE( Operand &op1 ) {
  this->push_back( new Instruction("JE", op1) );
}

void AssemblyBlock::JG( Operand &op1 ) {
  this->push_back( new Instruction("JG", op1) );
}

void AssemblyBlock::JGE( Operand &op1 ) {
  this->push_back( new Instruction("JGE", op1) );
}

void AssemblyBlock::JL( Operand &op1 ) {
  this->push_back( new Instruction("JL", op1) );
}

void AssemblyBlock::JLE( Operand &op1 ) {
  this->push_back( new Instruction("JLE", op1) );
}

void AssemblyBlock::JNA( Operand &op1 ) {
  this->push_back( new Instruction("JNA", op1) );
}

void AssemblyBlock::JNAE( Operand &op1 ) {
  this->push_back( new Instruction("JNAE", op1) );
}

void AssemblyBlock::JNB( Operand &op1 ) {
  this->push_back( new Instruction("JNB", op1) );
}

void AssemblyBlock::JNBE( Operand &op1 ) {
  this->push_back( new Instruction("JNBE", op1) );
}

void AssemblyBlock::JNC( Operand &op1 ) {
  this->push_back( new Instruction("JNC", op1) );
}

void AssemblyBlock::JNE( Operand &op1 ) {
  this->push_back( new Instruction("JNE", op1) );
}

void AssemblyBlock::JNG( Operand &op1 ) {
  this->push_back( new Instruction("JNG", op1) );
}

void AssemblyBlock::JNGE( Operand &op1 ) {
  this->push_back( new Instruction("JNGE", op1) );
}

void AssemblyBlock::JNL( Operand &op1 ) {
  this->push_back( new Instruction("JNL", op1) );
}

void AssemblyBlock::JNLE( Operand &op1 ) {
  this->push_back( new Instruction("JNLE", op1) );
}

void AssemblyBlock::JNO( Operand &op1 ) {
  this->push_back( new Instruction("JNO", op1) );
}

void AssemblyBlock::JNP( Operand &op1 ) {
  this->push_back( new Instruction("JNP", op1) );
}

void AssemblyBlock::JNS( Operand &op1 ) {
  this->push_back( new Instruction("JNS", op1) );
}

void AssemblyBlock::JNZ( Operand &op1 ) {
  this->push_back( new Instruction("JNZ", op1) );
}

void AssemblyBlock::JO( Operand &op1 ) {
  this->push_back( new Instruction("JO", op1) );
}

void AssemblyBlock::JP( Operand &op1 ) {
  this->push_back( new Instruction("JP", op1) );
}

void AssemblyBlock::JPE( Operand &op1 ) {
  this->push_back( new Instruction("JPE", op1) );
}

void AssemblyBlock::JPO( Operand &op1 ) {
  this->push_back( new Instruction("JPO", op1) );
}

void AssemblyBlock::JS( Operand &op1 ) {
  this->push_back( new Instruction("JS", op1) );
}

void AssemblyBlock::JZ( Operand &op1 ) {
  this->push_back( new Instruction("JZ", op1) );
}

void AssemblyBlock::JMP( Operand &op1 ) {
  this->push_back( new Instruction("JMP", op1) );
}

void AssemblyBlock::JMP_FAR( Operand &op1 ) {
  this->push_back( new Instruction("JMP_FAR", op1) );
}

void AssemblyBlock::LAHF() {
  this->push_back( new Instruction("LAHF") );
}

void AssemblyBlock::LAR( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("LAR", op1, op2) );
}

void AssemblyBlock::LDS( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("LDS", op1, op2) );
}

void AssemblyBlock::LES( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("LES", op1, op2) );
}

void AssemblyBlock::LFS( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("LFS", op1, op2) );
}

void AssemblyBlock::LGS( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("LGS", op1, op2) );
}

void AssemblyBlock::LSS( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("LSS", op1, op2) );
}

void AssemblyBlock::LEA( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("LEA", op1, op2) );
}

void AssemblyBlock::LEAVE() {
  this->push_back( new Instruction("LEAVE") );
}

void AssemblyBlock::LGDT( Operand &op1 ) {
  this->push_back( new Instruction("LGDT", op1) );
}

void AssemblyBlock::LIDT( Operand &op1 ) {
  this->push_back( new Instruction("LIDT", op1) );
}

void AssemblyBlock::LLDT( Operand &op1 ) {
  this->push_back( new Instruction("LLDT", op1) );
}

void AssemblyBlock::LOCK() {
  this->push_back( new Instruction("LOCK") );
}

void AssemblyBlock::LODSB() {
  this->push_back( new Instruction("LODSB") );
}

void AssemblyBlock::LODSW() {
  this->push_back( new Instruction("LODSW") );
}

void AssemblyBlock::LODSD() {
  this->push_back( new Instruction("LODSD") );
}

void AssemblyBlock::LOOP( Operand &op1 ) {
  this->push_back( new Instruction("LOOP", op1) );
}

void AssemblyBlock::LOOPE( Operand &op1 ) {
  this->push_back( new Instruction("LOOPE", op1) );
}

void AssemblyBlock::LOOPNE( Operand &op1 ) {
  this->push_back( new Instruction("LOOPNE", op1) );
}

void AssemblyBlock::LSL( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("LSL", op1, op2) );
}

void AssemblyBlock::LTR( Operand &op1 ) {
  this->push_back( new Instruction("LTR", op1) );
}

void AssemblyBlock::MOV( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("MOV", op1, op2) );
}

void AssemblyBlock::MOVSB() {
  this->push_back( new Instruction("MOVSB") );
}

void AssemblyBlock::MOVSW() {
  this->push_back( new Instruction("MOVSW") );
}

void AssemblyBlock::MOVSD() {
  this->push_back( new Instruction("MOVSD") );
}

void AssemblyBlock::MOVSX( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("MOVSX", op1, op2) );
}

void AssemblyBlock::MOVZX( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("MOVZX", op1, op2) );
}

void AssemblyBlock::MUL( Operand &op1 ) {
  this->push_back( new Instruction("MUL", op1) );
}

void AssemblyBlock::NEG( Operand &op1 ) {
  this->push_back( new Instruction("NEG", op1) );
}

void AssemblyBlock::NOP() {
  this->push_back( new Instruction("NOP") );
}

void AssemblyBlock::OR( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("OR", op1, op2) );
}

void AssemblyBlock::OUT( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("OUT", op1, op2) );
}

void AssemblyBlock::OUTSB() {
  this->push_back( new Instruction("OUTSB") );
}

void AssemblyBlock::OUTSW() {
  this->push_back( new Instruction("OUTSW") );
}

void AssemblyBlock::OUTSD() {
  this->push_back( new Instruction("OUTSD") );
}

void AssemblyBlock::POP( Operand &op1 ) {
  this->push_back( new Instruction("POP", op1) );
}

void AssemblyBlock::POPA() {
  this->push_back( new Instruction("POPA") );
}

void AssemblyBlock::POPAD() {
  this->push_back( new Instruction("POPAD") );
}

void AssemblyBlock::POPF() {
  this->push_back( new Instruction("POPF") );
}

void AssemblyBlock::POPFD() {
  this->push_back( new Instruction("POPFD") );
}

void AssemblyBlock::PUSH( Operand &op1 ) {
  this->push_back( new Instruction("PUSH", op1) );
}

void AssemblyBlock::PUSHA() {
  this->push_back( new Instruction("PUSHA") );
}

void AssemblyBlock::PUSHAD() {
  this->push_back( new Instruction("PUSHAD") );
}

void AssemblyBlock::PUSHF() {
  this->push_back( new Instruction("PUSHF") );
}

void AssemblyBlock::PUSHFD() {
  this->push_back( new Instruction("PUSHFD") );
}

void AssemblyBlock::RCL( Operand &op1 ) {
  this->push_back( new Instruction("RCL", op1) );
}

void AssemblyBlock::RCL( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("RCL", op1, op2) );
}

void AssemblyBlock::RCR( Operand &op1 ) {
  this->push_back( new Instruction("RCR", op1) );
}

void AssemblyBlock::RCR( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("RCR", op1, op2) );
}

void AssemblyBlock::REP() {
  this->push_back( new Instruction("REP") );
}

void AssemblyBlock::REPE() {
  this->push_back( new Instruction("REPE") );
}

void AssemblyBlock::REPNE() {
  this->push_back( new Instruction("REPNE") );
}

void AssemblyBlock::RET() {
  this->push_back( new Instruction("RET") );
}

void AssemblyBlock::RET( Operand &op1 ) {
  this->push_back( new Instruction("RET", op1) );
}

void AssemblyBlock::RETF() {
  this->push_back( new Instruction("RETF") );
}

void AssemblyBlock::RETF( Operand &op1 ) {
  this->push_back( new Instruction("RETF", op1) );
}

void AssemblyBlock::ROL( Operand &op1 ) {
  this->push_back( new Instruction("ROL", op1) );
}

void AssemblyBlock::ROL( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("ROL", op1, op2) );
}

void AssemblyBlock::ROR( Operand &op1 ) {
  this->push_back( new Instruction("ROR", op1) );
}

void AssemblyBlock::ROR( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("ROR", op1, op2) );
}

void AssemblyBlock::SAHF() {
  this->push_back( new Instruction("SAHF") );
}

void AssemblyBlock::SAL( Operand &op1 ) {
  this->push_back( new Instruction("SAL", op1) );
}

void AssemblyBlock::SAL( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("SAL", op1, op2) );
}

void AssemblyBlock::SAR( Operand &op1 ) {
  this->push_back( new Instruction("SAR", op1) );
}

void AssemblyBlock::SAR( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("SAR", op1, op2) );
}

void AssemblyBlock::SBB( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("SBB", op1, op2) );
}

void AssemblyBlock::SCASB() {
  this->push_back( new Instruction("SCASB") );
}

void AssemblyBlock::SCASW() {
  this->push_back( new Instruction("SCASW") );
}

void AssemblyBlock::SCASD() {
  this->push_back( new Instruction("SCASD") );
}

void AssemblyBlock::SETA( Operand &op1 ) {
  this->push_back( new Instruction("SETA", op1) );
}

void AssemblyBlock::SETAE( Operand &op1 ) {
  this->push_back( new Instruction("SETAE", op1) );
}

void AssemblyBlock::SETB( Operand &op1 ) {
  this->push_back( new Instruction("SETB", op1) );
}

void AssemblyBlock::SETBE( Operand &op1 ) {
  this->push_back( new Instruction("SETBE", op1) );
}

void AssemblyBlock::SETC( Operand &op1 ) {
  this->push_back( new Instruction("SETC", op1) );
}

void AssemblyBlock::SETE( Operand &op1 ) {
  this->push_back( new Instruction("SETE", op1) );
}

void AssemblyBlock::SETG( Operand &op1 ) {
  this->push_back( new Instruction("SETG", op1) );
}

void AssemblyBlock::SETGE( Operand &op1 ) {
  this->push_back( new Instruction("SETGE", op1) );
}

void AssemblyBlock::SETL( Operand &op1 ) {
  this->push_back( new Instruction("SETL", op1) );
}

void AssemblyBlock::SETLE( Operand &op1 ) {
  this->push_back( new Instruction("SETLE", op1) );
}

void AssemblyBlock::SETNA( Operand &op1 ) {
  this->push_back( new Instruction("SETNA", op1) );
}

void AssemblyBlock::SETNAE( Operand &op1 ) {
  this->push_back( new Instruction("SETNAE", op1) );
}

void AssemblyBlock::SETNB( Operand &op1 ) {
  this->push_back( new Instruction("SETNB", op1) );
}

void AssemblyBlock::SETNBE( Operand &op1 ) {
  this->push_back( new Instruction("SETNBE", op1) );
}

void AssemblyBlock::SETNE( Operand &op1 ) {
  this->push_back( new Instruction("SETNE", op1) );
}

void AssemblyBlock::SETNG( Operand &op1 ) {
  this->push_back( new Instruction("SETNG", op1) );
}

void AssemblyBlock::SETNGE( Operand &op1 ) {
  this->push_back( new Instruction("SETNGE", op1) );
}

void AssemblyBlock::SETNL( Operand &op1 ) {
  this->push_back( new Instruction("SETNL", op1) );
}

void AssemblyBlock::SETNLE( Operand &op1 ) {
  this->push_back( new Instruction("SETNLE", op1) );
}

void AssemblyBlock::SETNO( Operand &op1 ) {
  this->push_back( new Instruction("SETNO", op1) );
}

void AssemblyBlock::SETNP( Operand &op1 ) {
  this->push_back( new Instruction("SETNP", op1) );
}

void AssemblyBlock::SETNS( Operand &op1 ) {
  this->push_back( new Instruction("SETNS", op1) );
}

void AssemblyBlock::SETNZ( Operand &op1 ) {
  this->push_back( new Instruction("SETNZ", op1) );
}

void AssemblyBlock::SETO( Operand &op1 ) {
  this->push_back( new Instruction("SETO", op1) );
}

void AssemblyBlock::SETP( Operand &op1 ) {
  this->push_back( new Instruction("SETP", op1) );
}

void AssemblyBlock::SETPE( Operand &op1 ) {
  this->push_back( new Instruction("SETPE", op1) );
}

void AssemblyBlock::SETPO( Operand &op1 ) {
  this->push_back( new Instruction("SETPO", op1) );
}

void AssemblyBlock::SETS( Operand &op1 ) {
  this->push_back( new Instruction("SETS", op1) );
}

void AssemblyBlock::SETZ( Operand &op1 ) {
  this->push_back( new Instruction("SETZ", op1) );
}

void AssemblyBlock::SGDT( Operand &op1 ) {
  this->push_back( new Instruction("SGDT", op1) );
}

void AssemblyBlock::SHDL( Operand &op1, Operand &op2, Operand &op3 ) {
  this->push_back( new Instruction("SHDL", op1, op2, op3) );
}

void AssemblyBlock::SHDR( Operand &op1, Operand &op2, Operand &op3 ) {
  this->push_back( new Instruction("SHDR", op1, op2, op3) );
}

void AssemblyBlock::SIDT( Operand &op1 ) {
  this->push_back( new Instruction("SIDT", op1) );
}

void AssemblyBlock::SLDT( Operand &op1 ) {
  this->push_back( new Instruction("SLDT", op1) );
}

void AssemblyBlock::SHL( Operand &op1 ) {
  this->push_back( new Instruction("SHL", op1) );
}

void AssemblyBlock::SHL( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("SHL", op1, op2) );
}

void AssemblyBlock::SHR( Operand &op1 ) {
  this->push_back( new Instruction("SHR", op1) );
}

void AssemblyBlock::SHR( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("SHR", op1, op2) );
}

void AssemblyBlock::STC() {
  this->push_back( new Instruction("STC") );
}

void AssemblyBlock::STD() {
  this->push_back( new Instruction("STD") );
}

void AssemblyBlock::STI() {
  this->push_back( new Instruction("STI") );
}

void AssemblyBlock::STOSB() {
  this->push_back( new Instruction("STOSB") );
}

void AssemblyBlock::STOSW() {
  this->push_back( new Instruction("STOSW") );
}

void AssemblyBlock::STOSD() {
  this->push_back( new Instruction("STOSD") );
}

void AssemblyBlock::STR( Operand &op1 ) {
  this->push_back( new Instruction("STR", op1) );
}

void AssemblyBlock::SUB( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("SUB", op1, op2) );
}

void AssemblyBlock::TEST( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("TEST", op1, op2) );
}

void AssemblyBlock::VERR( Operand &op1 ) {
  this->push_back( new Instruction("VERR", op1) );
}

void AssemblyBlock::VERW( Operand &op1 ) {
  this->push_back( new Instruction("VERW", op1) );
}

void AssemblyBlock::WAIT() {
  this->push_back( new Instruction("WAIT") );
}

void AssemblyBlock::XCHG( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("XCHG", op1, op2) );
}

void AssemblyBlock::XLAT() {
  this->push_back( new Instruction("XLAT") );
}

void AssemblyBlock::XOR( Operand &op1, Operand &op2 ) {
  this->push_back( new Instruction("XOR", op1, op2) );
}

void AssemblyBlock::push_back( Instruction* i ) {
  if(!first) {
    first = i;
    last = i;
  } else {
    last->next = i;
    last = i;
  }
}  
