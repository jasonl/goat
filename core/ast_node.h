#ifndef AST_NODE_H
#define AST_NODE_H

struct _Token;

class ASTNode {
 public:
  enum NODE_TYPE {
    SourceFile,
    Block,
    StatementGroup, Statement, ClassStatement, My,
    MutableAssignment, ImmutableAssignment,
    Conditional,
    ClassDefinition,
    FunctionDef, OneLineFunctionDef, BlockFunctionDef,
    ParameterDef,
    FunctionCall, Parameter, NamedParameter,
    IntegerLiteral, Variable, StringLiteral, NullLiteral,
    ReturnStatement
  };

  ASTNode( enum NODE_TYPE );
  void append( ASTNode* );
  enum NODE_TYPE type;
  struct _Token *token;
  ASTNode *parent;
  ASTNode *firstChild;
  ASTNode *nextSibling;
  ASTNode *prevSibling;
};

#endif
