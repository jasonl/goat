#ifndef __INTEGER_LITERAL_NODE_H
#define __INTEGER_LITERAL_NODE_H

class IntegerLiteralNode : public ASTNode {
 public:
 IntegerLiteralNode( const std::string &_contents ) : contents(_contents) {};
	void GenerateCode(AssemblyBlock*) const;
	void PushOntoStack(AssemblyBlock*) const;
  std::string Print() const { return "IntegerLiteral: " + contents; }
  int32_t Value() const;
#ifdef GOATTEST
  std::string Contents() const { return contents; }
#endif
 private:
  const std::string contents;
};

#endif
