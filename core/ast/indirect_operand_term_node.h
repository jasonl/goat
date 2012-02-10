#ifndef __INDIRECT_OPERAND_TERM_NODE_H
#define __INDIRECT_OPERAND_TERM_NODE_H

class IndirectOperandTermNode : public OperandNode {
 public:
   IndirectOperandTermNode(const std::string &_operation) : operation(_operation) {};
   std::string Print() const { return "IndirectOperandTerm: " + operation; }
   Operand *ModifyOperand(Operand*) const;

#ifdef GOATTEST
	std::string Operation() const { return operation; }
#endif

 private:
	const std::string operation;
};

#endif
