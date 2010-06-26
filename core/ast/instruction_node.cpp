#include "../ast_node.h"
#include "../lexer.h"
#include "../i386/instruction.h"

InstructionNode::InstructionNode( TokenIterator &_token ): 
  ASTNode( ASTNode::Instruction ) {
  token = &(*_token);
}

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

  ins = new ::Instruction( Content(), operands[0], operands[1], operands[2]);
  a->AppendInstruction(ins);
  return a;
}