#ifndef __SOURCE_FILE_NODE_H
#define __SOURCE_FILE_NODE_H

class SourceFileNode : public ASTNode {
 public:
	SourceFileNode() {};
	void Analyse( Scope* );
	AssemblyBlock *GenerateCode();
	std::string Print() const { return "SourceFile: " + scope->GetSourceFile()->FileName(); }
 private:
  ClassDefinitionNode *globalObject;
};

#endif
