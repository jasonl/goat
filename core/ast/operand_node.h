#ifndef __OPERAND_NODE_H
#define __OPERAND_NODE_H

class OperandNode : public ASTNode {
  OperandNode *nextOperand;
  friend class InstructionNode;
  friend class OperandIterator;
 public:
 OperandNode( ASTNode::NODE_TYPE _t ) : ASTNode(_t) {};
  virtual Operand *GenerateOperand() const { return NULL; }
};

class OperandIterator {
  OperandNode *p;
public:
  OperandIterator( OperandNode* start) : p(start) {}
  OperandIterator( const OperandIterator& asti ) : p(asti.p) {}
  OperandIterator operator++() {p = p->nextOperand; return *this;}
  OperandIterator operator++(int) { p = p->nextOperand; return *this;}
  bool operator==( const OperandIterator& asti ) { return asti.p == p; }
  bool operator!=( const OperandIterator& asti ) { return asti.p != p; }
  OperandNode& operator*() { return *p; }
  OperandNode* operator->() { return p; }
};

#endif
