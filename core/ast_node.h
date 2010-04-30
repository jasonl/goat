#ifndef AST_NODE_H
#define AST_NODE_H

struct _Token;
class Scope;
class AssemblyBlock;

const std::string NODE_TYPES[] = { 
  "SourceFile",
  "\x1b[1;33mBlock\x1b[0;37;00m",
  "StatementGroup", "Statement", "ClassStatement", "My",
  "\x1b[0;36mMutableAssignment\x1b[0;37;00m", "\x1b[0;36mImmutableAssignment\x1b[0;37;00m",
  "\x1b[1;35mConditional\x1b[0;37;00m",
  "ClassDefinition",
  "\x1b[1;31mFunctionDef\x1b[0;37;00m", "OneLineFunctionDef", "BlockFunctionDef",
  "ParameterDef",
  "\x1b[1;34mFunctionCall\x1b[0;37;00m", "Parameter", "NamedParameter",
  "IntegerLiteral", "Variable", "StringLiteral", "NullLiteral",
  "\x1b[1;32mReturnStatement\x1b[0;37;00m"
};

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
  ~ASTNode();

  void append( ASTNode* );
  void InsertFirstChild( ASTNode* );

  virtual void Analyse( Scope* );
  AssemblyBlock* GenerateCode();

  enum NODE_TYPE type;
  struct _Token *token;
  Scope *scope;
  ASTNode *parent;
  ASTNode *firstChild;
  ASTNode *nextSibling;
  ASTNode *prevSibling;
};

#define MATCHER_FOR(name) ASTNode *Parser::Match##name()

// Include the derived classes here for convenience
#include "ast_block_node.h"
#include "ast_string_literal_node.hpp"
#include "ast_integer_literal_node.hpp"
#include "ast_variable_node.hpp"

#endif
