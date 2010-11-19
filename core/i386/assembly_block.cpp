#include "assembly_block.h"

void AssemblyBlock::AAA() {
  AppendInstruction( new Instruction("AAA") );
}

void AssemblyBlock::AAD() {
  AppendInstruction( new Instruction("AAD") );
}

void AssemblyBlock::AAM() {
  AppendInstruction( new Instruction("AAM") );
}

void AssemblyBlock::AAS() {
  AppendInstruction( new Instruction("AAS") );
}

void AssemblyBlock::ADC( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("ADC", &op1, &op2) );
}

void AssemblyBlock::ADD( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("ADD", &op1, &op2) );
}

void AssemblyBlock::AND( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("AND", &op1, &op2) );
}

void AssemblyBlock::ARPL( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("ARPL", &op1, &op2) );
}

void AssemblyBlock::BOUND( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("BOUND", &op1, &op2) );
}

void AssemblyBlock::BSF( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("BSF", &op1, &op2) );
}

void AssemblyBlock::BSR( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("BSR", &op1, &op2) );
}

void AssemblyBlock::BSWAP( Operand &op1 ) {
  AppendInstruction( new Instruction("BSWAP", &op1) );
}

void AssemblyBlock::BT( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("BT", &op1, &op2) );
}

void AssemblyBlock::BTC( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("BTC", &op1, &op2) );
}

void AssemblyBlock::BTR( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("BTR", &op1, &op2) );
}

void AssemblyBlock::BTS( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("BTS", &op1, &op2) );
}

void AssemblyBlock::CALL( Operand &op1 ) {
  AppendInstruction( new Instruction("CALL", &op1) );
}

void AssemblyBlock::CALL_FAR( Operand &op1 ) {
  AppendInstruction( new Instruction("CALL_FAR", &op1) );
}

void AssemblyBlock::CBW() {
  AppendInstruction( new Instruction("CBW") );
}

void AssemblyBlock::CWD() {
  AppendInstruction( new Instruction("CWD") );
}

void AssemblyBlock::CDW() {
  AppendInstruction( new Instruction("CDW") );
}

void AssemblyBlock::CWDE() {
  AppendInstruction( new Instruction("CWDE") );
}

void AssemblyBlock::CLC() {
  AppendInstruction( new Instruction("CLC") );
}

void AssemblyBlock::CLD() {
  AppendInstruction( new Instruction("CLD") );
}

void AssemblyBlock::CLI() {
  AppendInstruction( new Instruction("CLI") );
}

void AssemblyBlock::CLTS() {
  AppendInstruction( new Instruction("CLTS") );
}

void AssemblyBlock::CMC() {
  AppendInstruction( new Instruction("CMC") );
}

void AssemblyBlock::CMP( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("CMP", &op1, &op2) );
}

void AssemblyBlock::CMPSB() {
  AppendInstruction( new Instruction("CMPSB") );
}

void AssemblyBlock::CMPSW() {
  AppendInstruction( new Instruction("CMPSW") );
}

void AssemblyBlock::CMPSD() {
  AppendInstruction( new Instruction("CMPSD") );
}

void AssemblyBlock::DAA() {
  AppendInstruction( new Instruction("DAA") );
}

void AssemblyBlock::DAS() {
  AppendInstruction( new Instruction("DAS") );
}

void AssemblyBlock::DEC( Operand &op1 ) {
  AppendInstruction( new Instruction("DEC", &op1) );
}

void AssemblyBlock::DIV( Operand &op1 ) {
  AppendInstruction( new Instruction("DIV", &op1) );
}

void AssemblyBlock::ENTER( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("ENTER", &op1, &op2) );
}

void AssemblyBlock::HLT() {
  AppendInstruction( new Instruction("HLT") );
}

void AssemblyBlock::IDIV( Operand &op1 ) {
  AppendInstruction( new Instruction("IDIV", &op1) );
}

void AssemblyBlock::IMUL( Operand &op1 ) {
  AppendInstruction( new Instruction("IMUL", &op1) );
}

void AssemblyBlock::IMUL( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("IMUL", &op1, &op2) );
}

void AssemblyBlock::IMUL( Operand &op1, Operand &op2, Operand &op3 ) {
  AppendInstruction( new Instruction("IMUL", &op1, &op2, &op3) );
}

void AssemblyBlock::IN( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("IN", &op1, &op2) );
}

void AssemblyBlock::INC( Operand &op1 ) {
  AppendInstruction( new Instruction("INC", &op1) );
}

void AssemblyBlock::INSB() {
  AppendInstruction( new Instruction("INSB") );
}

void AssemblyBlock::INSW() {
  AppendInstruction( new Instruction("INSW") );
}

void AssemblyBlock::INSD() {
  AppendInstruction( new Instruction("INSD") );
}

void AssemblyBlock::INT( Operand &op1 ) {
  AppendInstruction( new Instruction("INT", &op1) );
}

void AssemblyBlock::INT3() {
  AppendInstruction( new Instruction("INT3") );
}

void AssemblyBlock::INTO() {
  AppendInstruction( new Instruction("INTO") );
}

void AssemblyBlock::INVTLB( Operand &op1 ) {
  AppendInstruction( new Instruction("INVTLB", &op1) );
}

void AssemblyBlock::IRET() {
  AppendInstruction( new Instruction("IRET") );
}

void AssemblyBlock::IRETW() {
  AppendInstruction( new Instruction("IRETW") );
}

void AssemblyBlock::IRETD() {
  AppendInstruction( new Instruction("IRETD") );
}

void AssemblyBlock::JA( Operand &op1 ) {
  AppendInstruction( new Instruction("JA", &op1) );
}

void AssemblyBlock::JAE( Operand &op1 ) {
  AppendInstruction( new Instruction("JAE", &op1) );
}

void AssemblyBlock::JB( Operand &op1 ) {
  AppendInstruction( new Instruction("JB", &op1) );
}

void AssemblyBlock::JBE( Operand &op1 ) {
  AppendInstruction( new Instruction("JBE", &op1) );
}

void AssemblyBlock::JC( Operand &op1 ) {
  AppendInstruction( new Instruction("JC", &op1) );
}

void AssemblyBlock::JE( Operand &op1 ) {
  AppendInstruction( new Instruction("JE", &op1) );
}

void AssemblyBlock::JG( Operand &op1 ) {
  AppendInstruction( new Instruction("JG", &op1) );
}

void AssemblyBlock::JGE( Operand &op1 ) {
  AppendInstruction( new Instruction("JGE", &op1) );
}

void AssemblyBlock::JL( Operand &op1 ) {
  AppendInstruction( new Instruction("JL", &op1) );
}

void AssemblyBlock::JLE( Operand &op1 ) {
  AppendInstruction( new Instruction("JLE", &op1) );
}

void AssemblyBlock::JNA( Operand &op1 ) {
  AppendInstruction( new Instruction("JNA", &op1) );
}

void AssemblyBlock::JNAE( Operand &op1 ) {
  AppendInstruction( new Instruction("JNAE", &op1) );
}

void AssemblyBlock::JNB( Operand &op1 ) {
  AppendInstruction( new Instruction("JNB", &op1) );
}

void AssemblyBlock::JNBE( Operand &op1 ) {
  AppendInstruction( new Instruction("JNBE", &op1) );
}

void AssemblyBlock::JNC( Operand &op1 ) {
  AppendInstruction( new Instruction("JNC", &op1) );
}

void AssemblyBlock::JNE( Operand &op1 ) {
  AppendInstruction( new Instruction("JNE", &op1) );
}

void AssemblyBlock::JNG( Operand &op1 ) {
  AppendInstruction( new Instruction("JNG", &op1) );
}

void AssemblyBlock::JNGE( Operand &op1 ) {
  AppendInstruction( new Instruction("JNGE", &op1) );
}

void AssemblyBlock::JNL( Operand &op1 ) {
  AppendInstruction( new Instruction("JNL", &op1) );
}

void AssemblyBlock::JNLE( Operand &op1 ) {
  AppendInstruction( new Instruction("JNLE", &op1) );
}

void AssemblyBlock::JNO( Operand &op1 ) {
  AppendInstruction( new Instruction("JNO", &op1) );
}

void AssemblyBlock::JNP( Operand &op1 ) {
  AppendInstruction( new Instruction("JNP", &op1) );
}

void AssemblyBlock::JNS( Operand &op1 ) {
  AppendInstruction( new Instruction("JNS", &op1) );
}

void AssemblyBlock::JNZ( Operand &op1 ) {
  AppendInstruction( new Instruction("JNZ", &op1) );
}

void AssemblyBlock::JO( Operand &op1 ) {
  AppendInstruction( new Instruction("JO", &op1) );
}

void AssemblyBlock::JP( Operand &op1 ) {
  AppendInstruction( new Instruction("JP", &op1) );
}

void AssemblyBlock::JPE( Operand &op1 ) {
  AppendInstruction( new Instruction("JPE", &op1) );
}

void AssemblyBlock::JPO( Operand &op1 ) {
  AppendInstruction( new Instruction("JPO", &op1) );
}

void AssemblyBlock::JS( Operand &op1 ) {
  AppendInstruction( new Instruction("JS", &op1) );
}

void AssemblyBlock::JZ( Operand &op1 ) {
  AppendInstruction( new Instruction("JZ", &op1) );
}

void AssemblyBlock::JMP( Operand &op1 ) {
  AppendInstruction( new Instruction("JMP", &op1) );
}

void AssemblyBlock::JMP_FAR( Operand &op1 ) {
  AppendInstruction( new Instruction("JMP_FAR", &op1) );
}

void AssemblyBlock::LAHF() {
  AppendInstruction( new Instruction("LAHF") );
}

void AssemblyBlock::LAR( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("LAR", &op1, &op2) );
}

void AssemblyBlock::LDS( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("LDS", &op1, &op2) );
}

void AssemblyBlock::LES( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("LES", &op1, &op2) );
}

void AssemblyBlock::LFS( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("LFS", &op1, &op2) );
}

void AssemblyBlock::LGS( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("LGS", &op1, &op2) );
}

void AssemblyBlock::LSS( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("LSS", &op1, &op2) );
}

void AssemblyBlock::LEA( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("LEA", &op1, &op2) );
}

void AssemblyBlock::LEAVE() {
  AppendInstruction( new Instruction("LEAVE") );
}

void AssemblyBlock::LGDT( Operand &op1 ) {
  AppendInstruction( new Instruction("LGDT", &op1) );
}

void AssemblyBlock::LIDT( Operand &op1 ) {
  AppendInstruction( new Instruction("LIDT", &op1) );
}

void AssemblyBlock::LLDT( Operand &op1 ) {
  AppendInstruction( new Instruction("LLDT", &op1) );
}

void AssemblyBlock::LOCK() {
  AppendInstruction( new Instruction("LOCK") );
}

void AssemblyBlock::LODSB() {
  AppendInstruction( new Instruction("LODSB") );
}

void AssemblyBlock::LODSW() {
  AppendInstruction( new Instruction("LODSW") );
}

void AssemblyBlock::LODSD() {
  AppendInstruction( new Instruction("LODSD") );
}

void AssemblyBlock::LOOP( Operand &op1 ) {
  AppendInstruction( new Instruction("LOOP", &op1) );
}

void AssemblyBlock::LOOPE( Operand &op1 ) {
  AppendInstruction( new Instruction("LOOPE", &op1) );
}

void AssemblyBlock::LOOPNE( Operand &op1 ) {
  AppendInstruction( new Instruction("LOOPNE", &op1) );
}

void AssemblyBlock::LSL( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("LSL", &op1, &op2) );
}

void AssemblyBlock::LTR( Operand &op1 ) {
  AppendInstruction( new Instruction("LTR", &op1) );
}

void AssemblyBlock::MOV( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("MOV", &op1, &op2) );
}

void AssemblyBlock::MOVSB() {
  AppendInstruction( new Instruction("MOVSB") );
}

void AssemblyBlock::MOVSW() {
  AppendInstruction( new Instruction("MOVSW") );
}

void AssemblyBlock::MOVSD() {
  AppendInstruction( new Instruction("MOVSD") );
}

void AssemblyBlock::MOVSX( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("MOVSX", &op1, &op2) );
}

void AssemblyBlock::MOVZX( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("MOVZX", &op1, &op2) );
}

void AssemblyBlock::MUL( Operand &op1 ) {
  AppendInstruction( new Instruction("MUL", &op1) );
}

void AssemblyBlock::NEG( Operand &op1 ) {
  AppendInstruction( new Instruction("NEG", &op1) );
}

void AssemblyBlock::NOP() {
  AppendInstruction( new Instruction("NOP") );
}

void AssemblyBlock::OR( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("OR", &op1, &op2) );
}

void AssemblyBlock::OUT( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("OUT", &op1, &op2) );
}

void AssemblyBlock::OUTSB() {
  AppendInstruction( new Instruction("OUTSB") );
}

void AssemblyBlock::OUTSW() {
  AppendInstruction( new Instruction("OUTSW") );
}

void AssemblyBlock::OUTSD() {
  AppendInstruction( new Instruction("OUTSD") );
}

void AssemblyBlock::POP( Operand &op1 ) {
  AppendInstruction( new Instruction("POP", &op1) );
}

void AssemblyBlock::POPA() {
  AppendInstruction( new Instruction("POPA") );
}

void AssemblyBlock::POPAD() {
  AppendInstruction( new Instruction("POPAD") );
}

void AssemblyBlock::POPF() {
  AppendInstruction( new Instruction("POPF") );
}

void AssemblyBlock::POPFD() {
  AppendInstruction( new Instruction("POPFD") );
}

void AssemblyBlock::PUSH( Operand &op1 ) {
  AppendInstruction( new Instruction("PUSH", &op1) );
}

void AssemblyBlock::PUSHA() {
  AppendInstruction( new Instruction("PUSHA") );
}

void AssemblyBlock::PUSHAD() {
  AppendInstruction( new Instruction("PUSHAD") );
}

void AssemblyBlock::PUSHF() {
  AppendInstruction( new Instruction("PUSHF") );
}

void AssemblyBlock::PUSHFD() {
  AppendInstruction( new Instruction("PUSHFD") );
}

void AssemblyBlock::RCL( Operand &op1 ) {
  AppendInstruction( new Instruction("RCL", &op1) );
}

void AssemblyBlock::RCL( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("RCL", &op1, &op2) );
}

void AssemblyBlock::RCR( Operand &op1 ) {
  AppendInstruction( new Instruction("RCR", &op1) );
}

void AssemblyBlock::RCR( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("RCR", &op1, &op2) );
}

void AssemblyBlock::REP() {
  AppendInstruction( new Instruction("REP") );
}

void AssemblyBlock::REPE() {
  AppendInstruction( new Instruction("REPE") );
}

void AssemblyBlock::REPNE() {
  AppendInstruction( new Instruction("REPNE") );
}

void AssemblyBlock::RET() {
  AppendInstruction( new Instruction("RET") );
}

void AssemblyBlock::RET( Operand &op1 ) {
  AppendInstruction( new Instruction("RET", &op1) );
}

void AssemblyBlock::RETF() {
  AppendInstruction( new Instruction("RETF") );
}

void AssemblyBlock::RETF( Operand &op1 ) {
  AppendInstruction( new Instruction("RETF", &op1) );
}

void AssemblyBlock::ROL( Operand &op1 ) {
  AppendInstruction( new Instruction("ROL", &op1) );
}

void AssemblyBlock::ROL( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("ROL", &op1, &op2) );
}

void AssemblyBlock::ROR( Operand &op1 ) {
  AppendInstruction( new Instruction("ROR", &op1) );
}

void AssemblyBlock::ROR( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("ROR", &op1, &op2) );
}

void AssemblyBlock::SAHF() {
  AppendInstruction( new Instruction("SAHF") );
}

void AssemblyBlock::SAL( Operand &op1 ) {
  AppendInstruction( new Instruction("SAL", &op1) );
}

void AssemblyBlock::SAL( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("SAL", &op1, &op2) );
}

void AssemblyBlock::SAR( Operand &op1 ) {
  AppendInstruction( new Instruction("SAR", &op1) );
}

void AssemblyBlock::SAR( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("SAR", &op1, &op2) );
}

void AssemblyBlock::SBB( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("SBB", &op1, &op2) );
}

void AssemblyBlock::SCASB() {
  AppendInstruction( new Instruction("SCASB") );
}

void AssemblyBlock::SCASW() {
  AppendInstruction( new Instruction("SCASW") );
}

void AssemblyBlock::SCASD() {
  AppendInstruction( new Instruction("SCASD") );
}

void AssemblyBlock::SETA( Operand &op1 ) {
  AppendInstruction( new Instruction("SETA", &op1) );
}

void AssemblyBlock::SETAE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETAE", &op1) );
}

void AssemblyBlock::SETB( Operand &op1 ) {
  AppendInstruction( new Instruction("SETB", &op1) );
}

void AssemblyBlock::SETBE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETBE", &op1) );
}

void AssemblyBlock::SETC( Operand &op1 ) {
  AppendInstruction( new Instruction("SETC", &op1) );
}

void AssemblyBlock::SETE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETE", &op1) );
}

void AssemblyBlock::SETG( Operand &op1 ) {
  AppendInstruction( new Instruction("SETG", &op1) );
}

void AssemblyBlock::SETGE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETGE", &op1) );
}

void AssemblyBlock::SETL( Operand &op1 ) {
  AppendInstruction( new Instruction("SETL", &op1) );
}

void AssemblyBlock::SETLE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETLE", &op1) );
}

void AssemblyBlock::SETNA( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNA", &op1) );
}

void AssemblyBlock::SETNAE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNAE", &op1) );
}

void AssemblyBlock::SETNB( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNB", &op1) );
}

void AssemblyBlock::SETNBE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNBE", &op1) );
}

void AssemblyBlock::SETNE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNE", &op1) );
}

void AssemblyBlock::SETNG( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNG", &op1) );
}

void AssemblyBlock::SETNGE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNGE", &op1) );
}

void AssemblyBlock::SETNL( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNL", &op1) );
}

void AssemblyBlock::SETNLE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNLE", &op1) );
}

void AssemblyBlock::SETNO( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNO", &op1) );
}

void AssemblyBlock::SETNP( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNP", &op1) );
}

void AssemblyBlock::SETNS( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNS", &op1) );
}

void AssemblyBlock::SETNZ( Operand &op1 ) {
  AppendInstruction( new Instruction("SETNZ", &op1) );
}

void AssemblyBlock::SETO( Operand &op1 ) {
  AppendInstruction( new Instruction("SETO", &op1) );
}

void AssemblyBlock::SETP( Operand &op1 ) {
  AppendInstruction( new Instruction("SETP", &op1) );
}

void AssemblyBlock::SETPE( Operand &op1 ) {
  AppendInstruction( new Instruction("SETPE", &op1) );
}

void AssemblyBlock::SETPO( Operand &op1 ) {
  AppendInstruction( new Instruction("SETPO", &op1) );
}

void AssemblyBlock::SETS( Operand &op1 ) {
  AppendInstruction( new Instruction("SETS", &op1) );
}

void AssemblyBlock::SETZ( Operand &op1 ) {
  AppendInstruction( new Instruction("SETZ", &op1) );
}

void AssemblyBlock::SGDT( Operand &op1 ) {
  AppendInstruction( new Instruction("SGDT", &op1) );
}

void AssemblyBlock::SHDL( Operand &op1, Operand &op2, Operand &op3 ) {
  AppendInstruction( new Instruction("SHDL", &op1, &op2, &op3) );
}

void AssemblyBlock::SHDR( Operand &op1, Operand &op2, Operand &op3 ) {
  AppendInstruction( new Instruction("SHDR", &op1, &op2, &op3) );
}

void AssemblyBlock::SIDT( Operand &op1 ) {
  AppendInstruction( new Instruction("SIDT", &op1) );
}

void AssemblyBlock::SLDT( Operand &op1 ) {
  AppendInstruction( new Instruction("SLDT", &op1) );
}

void AssemblyBlock::SHL( Operand &op1 ) {
  AppendInstruction( new Instruction("SHL", &op1) );
}

void AssemblyBlock::SHL( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("SHL", &op1, &op2) );
}

void AssemblyBlock::SHR( Operand &op1 ) {
  AppendInstruction( new Instruction("SHR", &op1) );
}

void AssemblyBlock::SHR( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("SHR", &op1, &op2) );
}

void AssemblyBlock::STC() {
  AppendInstruction( new Instruction("STC") );
}

void AssemblyBlock::STD() {
  AppendInstruction( new Instruction("STD") );
}

void AssemblyBlock::STI() {
  AppendInstruction( new Instruction("STI") );
}

void AssemblyBlock::STOSB() {
  AppendInstruction( new Instruction("STOSB") );
}

void AssemblyBlock::STOSW() {
  AppendInstruction( new Instruction("STOSW") );
}

void AssemblyBlock::STOSD() {
  AppendInstruction( new Instruction("STOSD") );
}

void AssemblyBlock::STR( Operand &op1 ) {
  AppendInstruction( new Instruction("STR", &op1) );
}

void AssemblyBlock::SUB( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("SUB", &op1, &op2) );
}

void AssemblyBlock::TEST( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("TEST", &op1, &op2) );
}

void AssemblyBlock::VERR( Operand &op1 ) {
  AppendInstruction( new Instruction("VERR", &op1) );
}

void AssemblyBlock::VERW( Operand &op1 ) {
  AppendInstruction( new Instruction("VERW", &op1) );
}

void AssemblyBlock::WAIT() {
  AppendInstruction( new Instruction("WAIT") );
}

void AssemblyBlock::XCHG( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("XCHG", &op1, &op2) );
}

void AssemblyBlock::XLAT() {
  AppendInstruction( new Instruction("XLAT") );
}

void AssemblyBlock::XOR( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("XOR", &op1, &op2) );
}

AssemblyBlock::AssemblyBlock() {
  last = NULL;
  first = NULL;
}

void AssemblyBlock::AppendBlock( AssemblyBlock *ab ) {
  if( ab == NULL || ab->first == NULL || ab->last == NULL ) return; 
  
  if( last ) {
    last->next = ab->first;
    last = ab->last;
  } else {
    first = ab->first;
    last = ab->last;
  }
  
  delete ab;
}

void AssemblyBlock::AppendInstruction( Instruction *i ) {
  if(first == NULL ) {
    first = i;
  } else {
    last->next = i;
  }
  last = i;
}

void AssemblyBlock::LabelFirstInstruction( std::string _label ) {
  if( first ) {
    first->SetLabel( _label );
  }
}

void AssemblyBlock::LabelLastInstruction( std::string _label ) {
  if( last ) {
    last->SetLabel( _label );
  }
}

void AssemblyBlock::CommentLastInstruction( std::string _comment ) {
  if( last ) {
    last->SetComment( _comment );
  }
}

void AssemblyBlock::AddHangingLabel( std::string _label ) {
  // TODO: Add support for genuinely empty instructions, and remove the NOP
  NOP();
  last->SetLabel( _label );
}
