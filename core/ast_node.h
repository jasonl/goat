#ifndef AST_NODE_H
#define AST_NODE_H

#include <list>
#include <string>
#include <stdint.h>
#include "token.hpp"
#include "scope.h"

#include "i386/operand.h"
#include "i386/assembly_block.h"

class ASTIterator;

typedef uint32_t Hash;
Hash goatHash( std::string );

const std::string NODE_TYPES[] = { 
  "SourceFile",
  "\x1b[1;33mBlock\x1b[0;37;00m",
  "StatementGroup", "Statement", "ClassStatement", "My",
  "\x1b[0;36mMutableAssignment\x1b[0;37;00m", "\x1b[0;36mImmutableAssignment\x1b[0;37;00m",
  "\x1b[1;35mConditional\x1b[0;37;00m",
  "ClassDefinition", "This",
  "\x1b[1;31mFunctionDef\x1b[0;37;00m", "OneLineFunctionDef", "BlockFunctionDef",
  "ParameterDef",
  "\x1b[1;34mFunctionCall\x1b[0;37;00m", "Parameter", "NamedParameter",
  "IntegerLiteral", "Variable", "StringLiteral", "NullLiteral",
  "\x1b[1;32mReturnStatement\x1b[0;37;00m",
  "\x1b[1;34mInlineAssembly\x1b[0;37;00m",
  "Instruction",
  "Label",
  "DirectOperand", "ImmediateOperand",
  "IndirectOperand", "IndirectOperandTerm"
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
    ClassDefinition, This,
    FunctionDef, OneLineFunctionDef, BlockFunctionDef,
    ParameterDef,
    FunctionCall, Parameter, NamedParameter,
    IntegerLiteral, Variable, StringLiteral, NullLiteral,
    ReturnStatement,
    InlineAssembly,
    Instruction,
    Label,
    DirectOperand, ImmediateOperand,
    IndirectOperand, IndirectOperandTerm
  };

  ASTNode( enum NODE_TYPE );
  ASTNode( enum NODE_TYPE, Token* );
  ~ASTNode();

  void append( ASTNode* );
  void AppendChild( ASTNode *_a ) { append(_a); }
  void InsertFirstChild( ASTNode* );
  void ReplaceChild( ASTNode*, ASTNode* );
  virtual ASTIterator ChildNodes();

  virtual void Analyse( Scope* );
  virtual AssemblyBlock* GenerateCode() { return NULL; }
  virtual AssemblyBlock* PushOntoStack() { return NULL; }

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

#include "ast/operand_node.h"

// Include the derived classes here for convenience
#include "ast/block_node.h"
#include "ast/ast_class_definition_node.hpp"
#include "ast/conditional_node.h"
#include "ast/direct_operand_node.h"
#include "ast/function_call_node.h"
#include "ast/function_def_node.h"
#include "ast/immediate_operand_node.h"
#include "ast/immutable_assignment_node.h"
#include "ast/ast_indirect_operand_node.hpp"
#include "ast/ast_indirect_operand_term_node.hpp"
#include "ast/inline_assembly_node.h"
#include "ast/instruction_node.h"
#include "ast/integer_literal_node.h"
#include "ast/ast_label_node.hpp"
#include "ast/mutable_assignment_node.h"
#include "ast/null_literal_node.h"
#include "ast/parameter_node.h"
#include "ast/parameter_def_node.h"
#include "ast/return_statement_node.h"
#include "ast/source_file_node.h"
#include "ast/ast_string_literal_node.hpp"
#include "ast/ast_this_node.hpp"
#include "ast/variable_node.h"

#endif
