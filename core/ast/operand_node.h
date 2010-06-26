#ifndef __OPERAND_NODE_H
#define __OPERAND_NODE_H

class OperandNode : public ASTNode {
  OperandNode *nextSibling;
  friend class OperandIterator;
 public:
 OperandNode( ASTNode::NODE_TYPE _t ) : ASTNode(_t) {};
  virtual Operand *GenerateOperand() { return NULL; }
};

class OperandIterator {
  OperandNode *p;
public:
  OperandIterator( OperandNode* start) : p(start) {}
  OperandIterator( const OperandIterator& asti ) : p(asti.p) {}
  OperandIterator operator++() {p = p->nextSibling; return *this;}
  OperandIterator operator++(int) { p = p->nextSibling; return *this;}
  bool operator==( const OperandIterator& asti ) { return asti.p == p; }
  bool operator!=( const OperandIterator& asti ) { return asti.p != p; }
  OperandNode& operator*() { return *p; }
  OperandNode* operator->() { return p; }
};

#endif
