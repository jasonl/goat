#ifndef AST_NODE_H
#define AST_NODE_H

#include <list>
#include <string>
#include "token.hpp"
#include "scope.h"

class AssemblyBlock;
class ASTIterator;

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
  friend class ASTIterator;
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
  ASTNode( enum NODE_TYPE, Token* );
  ~ASTNode();

  void append( ASTNode* );
  void InsertFirstChild( ASTNode* );
  virtual ASTIterator ChildNodes();

  virtual void Analyse( Scope* );
  AssemblyBlock* GenerateCode();

  void print(int, int, char*);
  std::string Content() { return token->Content(); }
  enum NODE_TYPE Type() { return type; }

  protected:
  enum NODE_TYPE type;
  Token *token;
  Scope *scope;
  ASTNode *parent;
  ASTNode *firstChild;
  ASTNode *nextSibling;
  ASTNode *prevSibling;
};

class ASTIterator {
  ASTNode *p;
public:
  ASTIterator( ASTNode* start) : p(start) {}
  ASTIterator( const ASTIterator& asti ) : p(asti.p) {}
  ASTIterator operator++() {p = p->nextSibling; return *this;}
  ASTIterator operator++(int) { p = p->nextSibling; return *this;}
  bool operator==( const ASTIterator& asti ) { return asti.p == p; }
  bool operator!=( const ASTIterator& asti ) { return asti.p != p; }
  ASTNode& operator*() { return *p; }
  ASTNode* operator->() { return p; }
};

typedef std::list<Token>::iterator TokenIterator;

// Include the derived classes here for convenience
#include "ast/ast_block_node.hpp"
#include "ast/ast_class_definition_node.hpp"
#include "ast/ast_conditional_node.hpp"
#include "ast/ast_function_call_node.hpp"
#include "ast/ast_function_def_node.hpp"
#include "ast/ast_immutable_assignment_node.hpp"
#include "ast/ast_integer_literal_node.hpp"
#include "ast/ast_mutable_assignment_node.hpp"
#include "ast/ast_null_literal_node.hpp"
#include "ast/ast_parameter_node.hpp"
#include "ast/ast_parameter_def_node.hpp"
#include "ast/ast_return_statement_node.hpp"
#include "ast/ast_source_file_node.hpp"
#include "ast/ast_string_literal_node.hpp"
#include "ast/ast_variable_node.hpp"

#endif
