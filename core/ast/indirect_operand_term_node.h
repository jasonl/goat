#ifndef __INDIRECT_OPERAND_TERM_NODE_H
#define __INDIRECT_OPERAND_TERM_NODE_H

class IndirectOperandTermNode : public ASTNode {
public:
 IndirectOperandTermNode(const std::string &_operation) : ASTNode(IndirectOperandTerm), operation(_operation) {};

#ifdef GOATTEST
	std::string Operation() const { return operation; }
#endif

 private:
	const std::string operation;
};

#endif
