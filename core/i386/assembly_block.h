#ifndef __ASSEMBLY_BLOCK_H
#define __ASSEMBLY_BLOCK_H
#include "operand.h"
#include "assembler_item.h"
#include "instruction.h"

class AssemblyBlock {
public:
  void AAA();
  void AAD();
  void AAM();
  void AAS();
  void ADC( Operand&, Operand& );
  void ADD( Operand&, Operand& );
  void AND( Operand&, Operand& );
  void ARPL( Operand&, Operand& );
  void BOUND( Operand&, Operand& );
  void BSF( Operand&, Operand& );
  void BSR( Operand&, Operand& );
  void BSWAP( Operand& );
  void BT( Operand&, Operand& );
  void BTC( Operand&, Operand& );
  void BTR( Operand&, Operand& );
  void BTS( Operand&, Operand& );
  void CALL( Operand& );
  void CALL_FAR( Operand& );
  void CBW();
  void CWD();
  void CDW();
  void CWDE();
  void CLC();
  void CLD();
  void CLI();
  void CLTS();
  void CMC();
  void CMP( Operand&, Operand& );
  void CMPSB();
  void CMPSW();
  void CMPSD();
  void DAA();
  void DAS();
  void DEC( Operand& );
  void DIV( Operand& );
  void ENTER( Operand&, Operand& );
  void HLT();
  void IDIV( Operand& );
  void IMUL( Operand& );
  void IMUL( Operand&, Operand& );
  void IMUL( Operand&, Operand&, Operand& );
  void IN( Operand&, Operand& );
  void INC( Operand& );
  void INSB();
  void INSW();
  void INSD();
  void INT( Operand& );
  void INT3();
  void INTO();
  void INVTLB( Operand& );
  void IRET();
  void IRETW();
  void IRETD();
  void JA( Operand& );
  void JAE( Operand& );
  void JB( Operand& );
  void JBE( Operand& );
  void JC( Operand& );
  void JE( Operand& );
  void JG( Operand& );
  void JGE( Operand& );
  void JL( Operand& );
  void JLE( Operand& );
  void JNA( Operand& );
  void JNAE( Operand& );
  void JNB( Operand& );
  void JNBE( Operand& );
  void JNC( Operand& );
  void JNE( Operand& );
  void JNG( Operand& );
  void JNGE( Operand& );
  void JNL( Operand& );
  void JNLE( Operand& );
  void JNO( Operand& );
  void JNP( Operand& );
  void JNS( Operand& );
  void JNZ( Operand& );
  void JO( Operand& );
  void JP( Operand& );
  void JPE( Operand& );
  void JPO( Operand& );
  void JS( Operand& );
  void JZ( Operand& );
  void JMP( Operand& );
  void JMP_FAR( Operand& );
  void LAHF();
  void LAR( Operand&, Operand& );
  void LDS( Operand&, Operand& );
  void LES( Operand&, Operand& );
  void LFS( Operand&, Operand& );
  void LGS( Operand&, Operand& );
  void LSS( Operand&, Operand& );
  void LEA( Operand&, Operand& );
  void LEAVE();
  void LGDT( Operand& );
  void LIDT( Operand& );
  void LLDT( Operand& );
  void LOCK();
  void LODSB();
  void LODSW();
  void LODSD();
  void LOOP( Operand& );
  void LOOPE( Operand& );
  void LOOPNE( Operand& );
  void LSL( Operand&, Operand& );
  void LTR( Operand& );
  void MOV( Operand&, Operand& );
  void MOVSB();
  void MOVSW();
  void MOVSD();
  void MOVSX( Operand&, Operand& );
  void MOVZX( Operand&, Operand& );
  void MUL( Operand& );
  void NEG( Operand& );
  void NOP();
  void OR( Operand&, Operand& );
  void OUT( Operand&, Operand& );
  void OUTSB();
  void OUTSW();
  void OUTSD();
  void POP( Operand& );
  void POPA();
  void POPAD();
  void POPF();
  void POPFD();
  void PUSH( Operand& );
  void PUSHA();
  void PUSHAD();
  void PUSHF();
  void PUSHFD();
  void RCL( Operand& );
  void RCL( Operand&, Operand& );
  void RCR( Operand& );
  void RCR( Operand&, Operand& );
  void REP();
  void REPE();
  void REPNE();
  void RET();
  void RET( Operand& );
  void RETF();
  void RETF( Operand& );
  void ROL( Operand& );
  void ROL( Operand&, Operand& );
  void ROR( Operand& );
  void ROR( Operand&, Operand& );
  void SAHF();
  void SAL( Operand& );
  void SAL( Operand&, Operand& );
  void SAR( Operand& );
  void SAR( Operand&, Operand& );
  void SBB( Operand&, Operand& );
  void SCASB();
  void SCASW();
  void SCASD();
  void SETA( Operand& );
  void SETAE( Operand& );
  void SETB( Operand& );
  void SETBE( Operand& );
  void SETC( Operand& );
  void SETE( Operand& );
  void SETG( Operand& );
  void SETGE( Operand& );
  void SETL( Operand& );
  void SETLE( Operand& );
  void SETNA( Operand& );
  void SETNAE( Operand& );
  void SETNB( Operand& );
  void SETNBE( Operand& );
  void SETNE( Operand& );
  void SETNG( Operand& );
  void SETNGE( Operand& );
  void SETNL( Operand& );
  void SETNLE( Operand& );
  void SETNO( Operand& );
  void SETNP( Operand& );
  void SETNS( Operand& );
  void SETNZ( Operand& );
  void SETO( Operand& );
  void SETP( Operand& );
  void SETPE( Operand& );
  void SETPO( Operand& );
  void SETS( Operand& );
  void SETZ( Operand& );
  void SGDT( Operand& );
  void SHDL( Operand&, Operand&, Operand& );
  void SHDR( Operand&, Operand&, Operand& );
  void SIDT( Operand& );
  void SLDT( Operand& );
  void SHL( Operand& );
  void SHL( Operand&, Operand& );
  void SHR( Operand& );
  void SHR( Operand&, Operand& );
  void STC();
  void STD();
  void STI();
  void STOSB();
  void STOSW();
  void STOSD();
  void STR( Operand& );
  void SUB( Operand&, Operand& );
  void TEST( Operand&, Operand& );
  void VERR( Operand& );
  void VERW( Operand& );
  void WAIT();
  void XCHG( Operand&, Operand& );
  void XLAT();
  void XOR( Operand&, Operand& );
  AssemblyBlock();
  void AppendBlock( AssemblyBlock* );
  void AppendInstruction( Instruction* );
  AssemblerItemIterator Instructions() { return AssemblerItemIterator( first ); }
  void LabelFirstInstruction( std::string );
  void LabelLastInstruction( std::string );
  void CommentLastInstruction( std::string );
  void AddHangingLabel( std::string );
 private:
  AssemblerItem *first;
  AssemblerItem *last;
};
#endif
