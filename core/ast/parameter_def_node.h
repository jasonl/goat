#ifndef __PARAMETER_DEF_NODE
#define __PARAMETER_DEF_NODE

class ParameterDefNode : public ASTNode {
 public:
    ParameterDefNode( const std::string &_name ) : name(_name) {};
	void Analyse( Scope* );
	const std::string& Name() const { return name; }
	std::string Print() const { return "ParameterDef: " + name; }
 private:
  const std::string name;
};

#endif
