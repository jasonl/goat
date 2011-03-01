#include "assembly_block.h"

void AssemblyBlock::aaa() {
  AppendInstruction( new Instruction("aaa") );
}

void AssemblyBlock::aad() {
  AppendInstruction( new Instruction("aad") );
}

void AssemblyBlock::aam() {
  AppendInstruction( new Instruction("aam") );
}

void AssemblyBlock::aas() {
  AppendInstruction( new Instruction("aas") );
}

void AssemblyBlock::adc( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("adc", &op1, &op2) );
}

void AssemblyBlock::add( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("add", &op1, &op2) );
}

void AssemblyBlock::_and( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("and", &op1, &op2) );
}

void AssemblyBlock::arpl( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("arpl", &op1, &op2) );
}

void AssemblyBlock::bound( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("bound", &op1, &op2) );
}

void AssemblyBlock::bsf( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("bsf", &op1, &op2) );
}

void AssemblyBlock::bsr( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("bsr", &op1, &op2) );
}

void AssemblyBlock::bswap( Operand &op1 ) {
  AppendInstruction( new Instruction("bswap", &op1) );
}

void AssemblyBlock::bt( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("bt", &op1, &op2) );
}

void AssemblyBlock::btc( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("btc", &op1, &op2) );
}

void AssemblyBlock::btr( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("btr", &op1, &op2) );
}

void AssemblyBlock::bts( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("bts", &op1, &op2) );
}

void AssemblyBlock::call( Operand &op1 ) {
  AppendInstruction( new Instruction("call", &op1) );
}

void AssemblyBlock::call_far( Operand &op1 ) {
  AppendInstruction( new Instruction("call_far", &op1) );
}

void AssemblyBlock::cbw() {
  AppendInstruction( new Instruction("cbw") );
}

void AssemblyBlock::cwd() {
  AppendInstruction( new Instruction("cwd") );
}

void AssemblyBlock::cdw() {
  AppendInstruction( new Instruction("cdw") );
}

void AssemblyBlock::cwde() {
  AppendInstruction( new Instruction("cwde") );
}

void AssemblyBlock::clc() {
  AppendInstruction( new Instruction("clc") );
}

void AssemblyBlock::cld() {
  AppendInstruction( new Instruction("cld") );
}

void AssemblyBlock::cli() {
  AppendInstruction( new Instruction("cli") );
}

void AssemblyBlock::clts() {
  AppendInstruction( new Instruction("clts") );
}

void AssemblyBlock::cmc() {
  AppendInstruction( new Instruction("cmc") );
}

void AssemblyBlock::cmp( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("cmp", &op1, &op2) );
}

void AssemblyBlock::cmpsb() {
  AppendInstruction( new Instruction("cmpsb") );
}

void AssemblyBlock::cmpsw() {
  AppendInstruction( new Instruction("cmpsw") );
}

void AssemblyBlock::cmpsd() {
  AppendInstruction( new Instruction("cmpsd") );
}

void AssemblyBlock::daa() {
  AppendInstruction( new Instruction("daa") );
}

void AssemblyBlock::das() {
  AppendInstruction( new Instruction("das") );
}

void AssemblyBlock::dec( Operand &op1 ) {
  AppendInstruction( new Instruction("dec", &op1) );
}

void AssemblyBlock::div( Operand &op1 ) {
  AppendInstruction( new Instruction("div", &op1) );
}

void AssemblyBlock::enter( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("enter", &op1, &op2) );
}

void AssemblyBlock::hlt() {
  AppendInstruction( new Instruction("hlt") );
}

void AssemblyBlock::idiv( Operand &op1 ) {
  AppendInstruction( new Instruction("idiv", &op1) );
}

void AssemblyBlock::imul( Operand &op1 ) {
  AppendInstruction( new Instruction("imul", &op1) );
}

void AssemblyBlock::imul( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("imul", &op1, &op2) );
}

void AssemblyBlock::imul( Operand &op1, Operand &op2, Operand &op3 ) {
  AppendInstruction( new Instruction("imul", &op1, &op2, &op3) );
}

void AssemblyBlock::in( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("in", &op1, &op2) );
}

void AssemblyBlock::inc( Operand &op1 ) {
  AppendInstruction( new Instruction("inc", &op1) );
}

void AssemblyBlock::insb() {
  AppendInstruction( new Instruction("insb") );
}

void AssemblyBlock::insw() {
  AppendInstruction( new Instruction("insw") );
}

void AssemblyBlock::insd() {
  AppendInstruction( new Instruction("insd") );
}

void AssemblyBlock::_int( Operand &op1 ) {
  AppendInstruction( new Instruction("int", &op1) );
}

void AssemblyBlock::int3() {
  AppendInstruction( new Instruction("int3") );
}

void AssemblyBlock::into() {
  AppendInstruction( new Instruction("into") );
}

void AssemblyBlock::invtlb( Operand &op1 ) {
  AppendInstruction( new Instruction("invtlb", &op1) );
}

void AssemblyBlock::iret() {
  AppendInstruction( new Instruction("iret") );
}

void AssemblyBlock::iretw() {
  AppendInstruction( new Instruction("iretw") );
}

void AssemblyBlock::iretd() {
  AppendInstruction( new Instruction("iretd") );
}

void AssemblyBlock::ja( Operand &op1 ) {
  AppendInstruction( new Instruction("ja", &op1) );
}

void AssemblyBlock::jae( Operand &op1 ) {
  AppendInstruction( new Instruction("jae", &op1) );
}

void AssemblyBlock::jb( Operand &op1 ) {
  AppendInstruction( new Instruction("jb", &op1) );
}

void AssemblyBlock::jbe( Operand &op1 ) {
  AppendInstruction( new Instruction("jbe", &op1) );
}

void AssemblyBlock::jc( Operand &op1 ) {
  AppendInstruction( new Instruction("jc", &op1) );
}

void AssemblyBlock::je( Operand &op1 ) {
  AppendInstruction( new Instruction("je", &op1) );
}

void AssemblyBlock::jg( Operand &op1 ) {
  AppendInstruction( new Instruction("jg", &op1) );
}

void AssemblyBlock::jge( Operand &op1 ) {
  AppendInstruction( new Instruction("jge", &op1) );
}

void AssemblyBlock::jl( Operand &op1 ) {
  AppendInstruction( new Instruction("jl", &op1) );
}

void AssemblyBlock::jle( Operand &op1 ) {
  AppendInstruction( new Instruction("jle", &op1) );
}

void AssemblyBlock::jna( Operand &op1 ) {
  AppendInstruction( new Instruction("jna", &op1) );
}

void AssemblyBlock::jnae( Operand &op1 ) {
  AppendInstruction( new Instruction("jnae", &op1) );
}

void AssemblyBlock::jnb( Operand &op1 ) {
  AppendInstruction( new Instruction("jnb", &op1) );
}

void AssemblyBlock::jnbe( Operand &op1 ) {
  AppendInstruction( new Instruction("jnbe", &op1) );
}

void AssemblyBlock::jnc( Operand &op1 ) {
  AppendInstruction( new Instruction("jnc", &op1) );
}

void AssemblyBlock::jne( Operand &op1 ) {
  AppendInstruction( new Instruction("jne", &op1) );
}

void AssemblyBlock::jng( Operand &op1 ) {
  AppendInstruction( new Instruction("jng", &op1) );
}

void AssemblyBlock::jnge( Operand &op1 ) {
  AppendInstruction( new Instruction("jnge", &op1) );
}

void AssemblyBlock::jnl( Operand &op1 ) {
  AppendInstruction( new Instruction("jnl", &op1) );
}

void AssemblyBlock::jnle( Operand &op1 ) {
  AppendInstruction( new Instruction("jnle", &op1) );
}

void AssemblyBlock::jno( Operand &op1 ) {
  AppendInstruction( new Instruction("jno", &op1) );
}

void AssemblyBlock::jnp( Operand &op1 ) {
  AppendInstruction( new Instruction("jnp", &op1) );
}

void AssemblyBlock::jns( Operand &op1 ) {
  AppendInstruction( new Instruction("jns", &op1) );
}

void AssemblyBlock::jnz( Operand &op1 ) {
  AppendInstruction( new Instruction("jnz", &op1) );
}

void AssemblyBlock::jo( Operand &op1 ) {
  AppendInstruction( new Instruction("jo", &op1) );
}

void AssemblyBlock::jp( Operand &op1 ) {
  AppendInstruction( new Instruction("jp", &op1) );
}

void AssemblyBlock::jpe( Operand &op1 ) {
  AppendInstruction( new Instruction("jpe", &op1) );
}

void AssemblyBlock::jpo( Operand &op1 ) {
  AppendInstruction( new Instruction("jpo", &op1) );
}

void AssemblyBlock::js( Operand &op1 ) {
  AppendInstruction( new Instruction("js", &op1) );
}

void AssemblyBlock::jz( Operand &op1 ) {
  AppendInstruction( new Instruction("jz", &op1) );
}

void AssemblyBlock::jmp( Operand &op1 ) {
  AppendInstruction( new Instruction("jmp", &op1) );
}

void AssemblyBlock::jmp_far( Operand &op1 ) {
  AppendInstruction( new Instruction("jmp_far", &op1) );
}

void AssemblyBlock::lahf() {
  AppendInstruction( new Instruction("lahf") );
}

void AssemblyBlock::lar( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("lar", &op1, &op2) );
}

void AssemblyBlock::lds( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("lds", &op1, &op2) );
}

void AssemblyBlock::les( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("les", &op1, &op2) );
}

void AssemblyBlock::lfs( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("lfs", &op1, &op2) );
}

void AssemblyBlock::lgs( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("lgs", &op1, &op2) );
}

void AssemblyBlock::lss( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("lss", &op1, &op2) );
}

void AssemblyBlock::lea( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("lea", &op1, &op2) );
}

void AssemblyBlock::leave() {
  AppendInstruction( new Instruction("leave") );
}

void AssemblyBlock::lgdt( Operand &op1 ) {
  AppendInstruction( new Instruction("lgdt", &op1) );
}

void AssemblyBlock::lidt( Operand &op1 ) {
  AppendInstruction( new Instruction("lidt", &op1) );
}

void AssemblyBlock::lldt( Operand &op1 ) {
  AppendInstruction( new Instruction("lldt", &op1) );
}

void AssemblyBlock::lock() {
  AppendInstruction( new Instruction("lock") );
}

void AssemblyBlock::lodsb() {
  AppendInstruction( new Instruction("lodsb") );
}

void AssemblyBlock::lodsw() {
  AppendInstruction( new Instruction("lodsw") );
}

void AssemblyBlock::lodsd() {
  AppendInstruction( new Instruction("lodsd") );
}

void AssemblyBlock::loop( Operand &op1 ) {
  AppendInstruction( new Instruction("loop", &op1) );
}

void AssemblyBlock::loope( Operand &op1 ) {
  AppendInstruction( new Instruction("loope", &op1) );
}

void AssemblyBlock::loopne( Operand &op1 ) {
  AppendInstruction( new Instruction("loopne", &op1) );
}

void AssemblyBlock::lsl( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("lsl", &op1, &op2) );
}

void AssemblyBlock::ltr( Operand &op1 ) {
  AppendInstruction( new Instruction("ltr", &op1) );
}

void AssemblyBlock::mov( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("mov", &op1, &op2) );
}

void AssemblyBlock::movsb() {
  AppendInstruction( new Instruction("movsb") );
}

void AssemblyBlock::movsw() {
  AppendInstruction( new Instruction("movsw") );
}

void AssemblyBlock::movsd() {
  AppendInstruction( new Instruction("movsd") );
}

void AssemblyBlock::movsx( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("movsx", &op1, &op2) );
}

void AssemblyBlock::movzx( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("movzx", &op1, &op2) );
}

void AssemblyBlock::mul( Operand &op1 ) {
  AppendInstruction( new Instruction("mul", &op1) );
}

void AssemblyBlock::neg( Operand &op1 ) {
  AppendInstruction( new Instruction("neg", &op1) );
}

void AssemblyBlock::nop() {
  AppendInstruction( new Instruction("nop") );
}

void AssemblyBlock::_or( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("or", &op1, &op2) );
}

void AssemblyBlock::out( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("out", &op1, &op2) );
}

void AssemblyBlock::outsb() {
  AppendInstruction( new Instruction("outsb") );
}

void AssemblyBlock::outsw() {
  AppendInstruction( new Instruction("outsw") );
}

void AssemblyBlock::outsd() {
  AppendInstruction( new Instruction("outsd") );
}

void AssemblyBlock::pop( Operand &op1 ) {
  AppendInstruction( new Instruction("pop", &op1) );
}

void AssemblyBlock::popa() {
  AppendInstruction( new Instruction("popa") );
}

void AssemblyBlock::popad() {
  AppendInstruction( new Instruction("popad") );
}

void AssemblyBlock::popf() {
  AppendInstruction( new Instruction("popf") );
}

void AssemblyBlock::popfd() {
  AppendInstruction( new Instruction("popfd") );
}

void AssemblyBlock::push( Operand &op1 ) {
  AppendInstruction( new Instruction("push", &op1) );
}

void AssemblyBlock::pusha() {
  AppendInstruction( new Instruction("pusha") );
}

void AssemblyBlock::pushad() {
  AppendInstruction( new Instruction("pushad") );
}

void AssemblyBlock::pushf() {
  AppendInstruction( new Instruction("pushf") );
}

void AssemblyBlock::pushfd() {
  AppendInstruction( new Instruction("pushfd") );
}

void AssemblyBlock::rcl( Operand &op1 ) {
  AppendInstruction( new Instruction("rcl", &op1) );
}

void AssemblyBlock::rcl( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("rcl", &op1, &op2) );
}

void AssemblyBlock::rcr( Operand &op1 ) {
  AppendInstruction( new Instruction("rcr", &op1) );
}

void AssemblyBlock::rcr( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("rcr", &op1, &op2) );
}

void AssemblyBlock::rep() {
  AppendInstruction( new Instruction("rep") );
}

void AssemblyBlock::repe() {
  AppendInstruction( new Instruction("repe") );
}

void AssemblyBlock::repne() {
  AppendInstruction( new Instruction("repne") );
}

void AssemblyBlock::ret() {
  AppendInstruction( new Instruction("ret") );
}

void AssemblyBlock::ret( Operand &op1 ) {
  AppendInstruction( new Instruction("ret", &op1) );
}

void AssemblyBlock::retf() {
  AppendInstruction( new Instruction("retf") );
}

void AssemblyBlock::retf( Operand &op1 ) {
  AppendInstruction( new Instruction("retf", &op1) );
}

void AssemblyBlock::rol( Operand &op1 ) {
  AppendInstruction( new Instruction("rol", &op1) );
}

void AssemblyBlock::rol( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("rol", &op1, &op2) );
}

void AssemblyBlock::ror( Operand &op1 ) {
  AppendInstruction( new Instruction("ror", &op1) );
}

void AssemblyBlock::ror( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("ror", &op1, &op2) );
}

void AssemblyBlock::sahf() {
  AppendInstruction( new Instruction("sahf") );
}

void AssemblyBlock::sal( Operand &op1 ) {
  AppendInstruction( new Instruction("sal", &op1) );
}

void AssemblyBlock::sal( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("sal", &op1, &op2) );
}

void AssemblyBlock::sar( Operand &op1 ) {
  AppendInstruction( new Instruction("sar", &op1) );
}

void AssemblyBlock::sar( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("sar", &op1, &op2) );
}

void AssemblyBlock::sbb( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("sbb", &op1, &op2) );
}

void AssemblyBlock::scasb() {
  AppendInstruction( new Instruction("scasb") );
}

void AssemblyBlock::scasw() {
  AppendInstruction( new Instruction("scasw") );
}

void AssemblyBlock::scasd() {
  AppendInstruction( new Instruction("scasd") );
}

void AssemblyBlock::seta( Operand &op1 ) {
  AppendInstruction( new Instruction("seta", &op1) );
}

void AssemblyBlock::setae( Operand &op1 ) {
  AppendInstruction( new Instruction("setae", &op1) );
}

void AssemblyBlock::setb( Operand &op1 ) {
  AppendInstruction( new Instruction("setb", &op1) );
}

void AssemblyBlock::setbe( Operand &op1 ) {
  AppendInstruction( new Instruction("setbe", &op1) );
}

void AssemblyBlock::setc( Operand &op1 ) {
  AppendInstruction( new Instruction("setc", &op1) );
}

void AssemblyBlock::sete( Operand &op1 ) {
  AppendInstruction( new Instruction("sete", &op1) );
}

void AssemblyBlock::setg( Operand &op1 ) {
  AppendInstruction( new Instruction("setg", &op1) );
}

void AssemblyBlock::setge( Operand &op1 ) {
  AppendInstruction( new Instruction("setge", &op1) );
}

void AssemblyBlock::setl( Operand &op1 ) {
  AppendInstruction( new Instruction("setl", &op1) );
}

void AssemblyBlock::setle( Operand &op1 ) {
  AppendInstruction( new Instruction("setle", &op1) );
}

void AssemblyBlock::setna( Operand &op1 ) {
  AppendInstruction( new Instruction("setna", &op1) );
}

void AssemblyBlock::setnae( Operand &op1 ) {
  AppendInstruction( new Instruction("setnae", &op1) );
}

void AssemblyBlock::setnb( Operand &op1 ) {
  AppendInstruction( new Instruction("setnb", &op1) );
}

void AssemblyBlock::setnbe( Operand &op1 ) {
  AppendInstruction( new Instruction("setnbe", &op1) );
}

void AssemblyBlock::setne( Operand &op1 ) {
  AppendInstruction( new Instruction("setne", &op1) );
}

void AssemblyBlock::setng( Operand &op1 ) {
  AppendInstruction( new Instruction("setng", &op1) );
}

void AssemblyBlock::setnge( Operand &op1 ) {
  AppendInstruction( new Instruction("setnge", &op1) );
}

void AssemblyBlock::setnl( Operand &op1 ) {
  AppendInstruction( new Instruction("setnl", &op1) );
}

void AssemblyBlock::setnle( Operand &op1 ) {
  AppendInstruction( new Instruction("setnle", &op1) );
}

void AssemblyBlock::setno( Operand &op1 ) {
  AppendInstruction( new Instruction("setno", &op1) );
}

void AssemblyBlock::setnp( Operand &op1 ) {
  AppendInstruction( new Instruction("setnp", &op1) );
}

void AssemblyBlock::setns( Operand &op1 ) {
  AppendInstruction( new Instruction("setns", &op1) );
}

void AssemblyBlock::setnz( Operand &op1 ) {
  AppendInstruction( new Instruction("setnz", &op1) );
}

void AssemblyBlock::seto( Operand &op1 ) {
  AppendInstruction( new Instruction("seto", &op1) );
}

void AssemblyBlock::setp( Operand &op1 ) {
  AppendInstruction( new Instruction("setp", &op1) );
}

void AssemblyBlock::setpe( Operand &op1 ) {
  AppendInstruction( new Instruction("setpe", &op1) );
}

void AssemblyBlock::setpo( Operand &op1 ) {
  AppendInstruction( new Instruction("setpo", &op1) );
}

void AssemblyBlock::sets( Operand &op1 ) {
  AppendInstruction( new Instruction("sets", &op1) );
}

void AssemblyBlock::setz( Operand &op1 ) {
  AppendInstruction( new Instruction("setz", &op1) );
}

void AssemblyBlock::sgdt( Operand &op1 ) {
  AppendInstruction( new Instruction("sgdt", &op1) );
}

void AssemblyBlock::shdl( Operand &op1, Operand &op2, Operand &op3 ) {
  AppendInstruction( new Instruction("shdl", &op1, &op2, &op3) );
}

void AssemblyBlock::shdr( Operand &op1, Operand &op2, Operand &op3 ) {
  AppendInstruction( new Instruction("shdr", &op1, &op2, &op3) );
}

void AssemblyBlock::sidt( Operand &op1 ) {
  AppendInstruction( new Instruction("sidt", &op1) );
}

void AssemblyBlock::sldt( Operand &op1 ) {
  AppendInstruction( new Instruction("sldt", &op1) );
}

void AssemblyBlock::shl( Operand &op1 ) {
  AppendInstruction( new Instruction("shl", &op1) );
}

void AssemblyBlock::shl( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("shl", &op1, &op2) );
}

void AssemblyBlock::shr( Operand &op1 ) {
  AppendInstruction( new Instruction("shr", &op1) );
}

void AssemblyBlock::shr( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("shr", &op1, &op2) );
}

void AssemblyBlock::stc() {
  AppendInstruction( new Instruction("stc") );
}

void AssemblyBlock::std() {
  AppendInstruction( new Instruction("std") );
}

void AssemblyBlock::sti() {
  AppendInstruction( new Instruction("sti") );
}

void AssemblyBlock::stosb() {
  AppendInstruction( new Instruction("stosb") );
}

void AssemblyBlock::stosw() {
  AppendInstruction( new Instruction("stosw") );
}

void AssemblyBlock::stosd() {
  AppendInstruction( new Instruction("stosd") );
}

void AssemblyBlock::str( Operand &op1 ) {
  AppendInstruction( new Instruction("str", &op1) );
}

void AssemblyBlock::sub( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("sub", &op1, &op2) );
}

void AssemblyBlock::test( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("test", &op1, &op2) );
}

void AssemblyBlock::verr( Operand &op1 ) {
  AppendInstruction( new Instruction("verr", &op1) );
}

void AssemblyBlock::verw( Operand &op1 ) {
  AppendInstruction( new Instruction("verw", &op1) );
}

void AssemblyBlock::wait() {
  AppendInstruction( new Instruction("wait") );
}

void AssemblyBlock::xchg( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("xchg", &op1, &op2) );
}

void AssemblyBlock::xlat() {
  AppendInstruction( new Instruction("xlat") );
}

void AssemblyBlock::_xor( Operand &op1, Operand &op2 ) {
  AppendInstruction( new Instruction("xor", &op1, &op2) );
}

AssemblyBlock::AssemblyBlock() {
  first = NULL;
  last = NULL;
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
  AppendItem(i);
}

void AssemblyBlock::AppendItem( AssemblerItem *i ) {  
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
  nop();
  last->SetLabel( _label );
}

void AssemblyBlock::SetSegment( std::string _segment ) {
  AppendItem( new SegmentDeclaration(_segment) );
}  

void AssemblyBlock::PrependItem( AssemblerItem *item ) {
  if(first == NULL) {
    first = item;
  } else {
    item->next = first;
    first = item;
  }
}
