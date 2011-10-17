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
  "\x1b[0;36mMutableAssignment\x1b[0;37;00m", "\x1b[0;36mConstantAssignment\x1b[0;37;00m",
  "\x1b[1;35mConditional\x1b[0;37;00m",
  "ClassDefinition", "ClassVariable", "Self",
  "\x1b[1;31mFunctionDef\x1b[0;37;00m", "OneLineFunctionDef", "BlockFunctionDef",
  "ParameterDef",
  "\x1b[1;34mFunctionCall\x1b[0;37;00m", "Parameter", "NamedParameter",
  "IntegerLiteral", "Variable", "StringLiteral", "NullLiteral",
  "\x1b[1;32mReturnStatement\x1b[0;37;00m",
  "\x1b[1;34mInlineAssembly\x1b[0;37;00m",
  "Instruction",
  "Label",
  "DirectOperand", "ImmediateOperand",
  "IndirectOperand", "IndirectOperandTerm",
  "HashOperand", "AddressOperand",
  "ObjectOperand"
};

class ASTNode {
  friend class ASTIterator;
 public:
  enum NODE_TYPE {
    SourceFile,
    Block,
    StatementGroup, Statement, ClassStatement, My,
    MutableAssignment, ConstantAssignment,
    Conditional,
    ClassDefinition, ClassVariable, Self, MethodAssignment, ClassMethodAssignment,
    FunctionDef, OneLineFunctionDef, BlockFunctionDef,
    ParameterDef,
    FunctionCall, Parameter, NamedParameter,
    IntegerLiteral, Variable, StringLiteral, NullLiteral,
    ReturnStatement,
    InlineAssembly,
    Instruction,
    Label,
    DirectOperand, ImmediateOperand,
    IndirectOperand, IndirectOperandTerm,
    HashOperand, AddressOperand,
    ObjectOperand
  };

  ASTNode( enum NODE_TYPE );
  ~ASTNode();

  ASTNode *FirstChild() { return firstChild; }

  void append( ASTNode* );
  void AppendChild( ASTNode *_a ) { append(_a); }
  void InsertFirstChild( ASTNode* );
  void ReplaceChild( ASTNode*, ASTNode* );
  void DetachChild( ASTNode* );
  ASTNode *MoveNodeTo( ASTNode* );
  virtual ASTIterator ChildNodes();

  ASTNode* MutableFindEnclosingNode(enum NODE_TYPE);
  const ASTNode *FindEnclosingNode(enum NODE_TYPE) const;

  virtual void Analyse( Scope* );
  virtual AssemblyBlock* GenerateCode() { return new AssemblyBlock(); }
  virtual AssemblyBlock* GetAuxiliaryCode();
  virtual AssemblyBlock* PushOntoStack() { return new AssemblyBlock(); }

  void print(int, int, char*);
  enum NODE_TYPE Type() { return type; }

 protected:
  enum NODE_TYPE type;
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
  ASTIterator operator--() {p = p->prevSibling; return *this;}
  ASTIterator operator--(int) { p = p->prevSibling; return *this;}
  bool operator==( const ASTIterator& asti ) { return asti.p == p; }
  bool operator!=( const ASTIterator& asti ) { return asti.p != p; }
  ASTNode& operator*() { return *p; }
  ASTNode* operator->() { return p; }
};

typedef std::list<Token>::iterator TokenIterator;

#include "ast/operand_node.h"

// Include the derived classes here for convenience
#include "ast/address_operand_node.h"
#include "ast/assignment_target_node.h"
#include "ast/block_node.h"
#include "ast/class_definition_node.h"
#include "ast/class_method_assignment_node.h"
#include "ast/class_variable_node.h"
#include "ast/conditional_node.h"
#include "ast/constant_assignment_node.h"
#include "ast/direct_operand_node.h"
#include "ast/function_call_node.h"
#include "ast/function_def_node.h"
#include "ast/hash_operand_node.h"
#include "ast/immediate_operand_node.h"
#include "ast/indirect_operand_node.h"
#include "ast/indirect_operand_term_node.h"
#include "ast/inline_assembly_node.h"
#include "ast/instruction_node.h"
#include "ast/integer_literal_node.h"
#include "ast/method_assignment_node.h"
#include "ast/mutable_assignment_node.h"
#include "ast/null_literal_node.h"
#include "ast/object_operand_node.h"
#include "ast/parameter_node.h"
#include "ast/parameter_def_node.h"
#include "ast/return_statement_node.h"
#include "ast/self_node.h"
#include "ast/source_file_node.h"
#include "ast/string_literal_node.h"
#include "ast/variable_node.h"

#endif
