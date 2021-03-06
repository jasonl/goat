#ifndef __OPERAND_NODE_H
#define __OPERAND_NODE_H

class OperandNode : public ASTNode {
  OperandNode *nextOperand;
  friend class InstructionNode;
  friend class OperandIterator;
 protected:
    Operand::OperandSize size;
	OperandNode *firstOperand;
	OperandNode *lastOperand;
 public:
	void AppendOperand(OperandNode*);
    OperandNode() : ASTNode(), nextOperand(NULL), size(Operand::None) {};
    void SetSize(Operand::OperandSize _size) { size = _size; }
	virtual Operand *GenerateOperand() const { std::cout << "fail"; return NULL; }
	virtual Operand *ModifyOperand(Operand* o) const { return o; }
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
