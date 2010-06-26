#ifndef __OPERAND_NODE_H
#define __OPERAND_NODE_H

class OperandNode : public ASTNode {
 public:
 OperandNode( ASTNode::NODE_TYPE _t ) : ASTNode(_t) {};
  virtual Operand *GenerateOperand() { return NULL; }
};

#endif
