#ifndef __HASH_OPERAND_NODE_H
#define __HASH_OPERAND_NODE_H

class HashOperandNode : public OperandNode {
 public:
 HashOperandNode(const std::string &_hashString) : hashString(_hashString) {};
  Operand *GenerateOperand() const;
  std::string Print() const { return "HashOperand: " + hashString; }
 private:
  const std::string hashString;
};

#endif
