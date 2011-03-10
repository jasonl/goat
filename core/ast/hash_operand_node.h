#ifndef __HASH_OPERAND_NODE_H
#define __HASH_OPERAND_NODE_H

class HashOperandNode : public OperandNode {
 public:
  HashOperandNode( Token& );
  Operand *GenerateOperand();
 private:
  std::string hashString;
};

#endif
