#include "../goat.h"
#include "../ast_node.h"
#include "../lexer.h"
#include "../i386/instruction.h"

AssemblyBlock *InstructionNode::GenerateCode() {
  AssemblyBlock *a = new AssemblyBlock;
  ::Instruction *ins = NULL;
  OperandIterator end(NULL);
  Operand *operands[3] = {NULL, NULL, NULL};
  int j = 0;

  for(OperandIterator i = Operands(); i != end; i++) {
    if( j >= 3 ) {
      // Uhh, we've a fourth operand.
      // TODO - raise an error;
      return NULL;
    }
    operands[j] = i->GenerateOperand();
    j++;
  }

  ins = new ::Instruction(mnemonic, operands[0], operands[1], operands[2]);

  if(label.length() > 0)
    ins->SetLabel( label );

  a->AppendInstruction(ins);
  return a;
}

void InstructionNode::AppendOperand( OperandNode *op ) {

  AppendChild( op );

  if( !firstOperand || !lastOperand ) {
    firstOperand = op;
    lastOperand = op;
  } else {
    lastOperand->nextOperand = op;
    lastOperand = op;
  }
}
