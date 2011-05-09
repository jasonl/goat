#ifndef __INDIRECT_OPERAND_TERM_NODE_H
#define __INDIRECT_OPERAND_TERM_NODE_H

class IndirectOperandTermNode : public ASTNode {
public:
 IndirectOperandTermNode(const std::string &_operation) : ASTNode(IndirectOperandTerm), operation(_operation) {};
 private:
	const std::string operation;
};

#endif
