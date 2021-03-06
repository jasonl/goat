#ifndef __RETURN_STATEMENT_NODE_H
#define __RETURN_STATEMENT_NODE_H

class ReturnStatementNode : public ASTNode {
public:
	ReturnStatementNode() {};
	void SetReturnValue( ASTNode* );
	ASTNode *ReturnExpr() { return returnValue; }
	ASTIterator ChildNodes();
	void Analyse( Scope* );
	AssemblyBlock *GenerateCode();
	std::string Print() const { return "ReturnStatement"; }
private:
  ASTNode *returnValue;
};

#endif
