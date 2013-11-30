#ifndef __INLINE_ASSEMBLY_NODE_H
#define __INLINE_ASSEMBLY_NODE_H

class InlineAssemblyNode : public ASTNode {
 public:
	InlineAssemblyNode() {};
	void Analyse( Scope* );
	void GenerateCode(AssemblyBlock*) const;
	std::string Print() const { return "InlineAssembly"; }
};

#endif
