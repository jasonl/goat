#ifndef __HASH_OPERAND_NODE_H
#define __HASH_OPERAND_NODE_H

class HashOperandNode : public OperandNode {
 public:
 HashOperandNode(const std::string &_hashString) : OperandNode(HashOperand), hashString(_hashString) {};
  Operand *GenerateOperand() const;
 private:
  const std::string hashString;
};

#endif
