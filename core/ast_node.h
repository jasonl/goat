#ifndef AST_NODE_H
#define AST_NODE_H

#include <list>
#include <string>
#include <stdint.h>
#include <iostream>
#include "token.hpp"
#include "scope.h"

#include "i386/operand.h"
#include "i386/assembly_block.h"

class ASTIterator;

typedef uint32_t Hash;
Hash goatHash( std::string );

const std::string red = "\x1b[1;31m";
const std::string yellow = "\x1b[1;33m";
const std::string cyan = "\x1b[0;36m";
const std::string reset = "\x1b[0;37;00m";

const std::string NODE_TYPES[] = {
  "AddressOperand",
  "Block",
  cyan + "ClassDefinition" + reset,
  "ClassLiteral",
  "ClassMethodAssignment",
  "ClassVariable",
  yellow + "Conditional" + reset,
  "ConstantAssignment",
  "DirectOperand",
  "ExternLabel",
  "FalseLiteral",
  "FunctionCall",
  "FunctionDef",
  "HashOperand",
  "ImmediateOperand",
  "IndirectOperand",
  "IndirectOperandTerm",
  "InlineAssembly",
  "Instruction",
  "IntegerLiteral",
  "Label",
  "MethodAssignment",
  "MutableAssignment",
  "NullLiteral",
  "ObjectOperand",
  "Parameter",
  "ParameterDef",
  red + "ReturnStatement" + reset,
  "Self",
  "SourceFile",
  "StringLiteral",
  "TrueLiteral",
  "Variable"
};

class ASTNode {
  friend class ASTIterator;
 public:
  enum NODE_TYPE {
	AddressOperand,
	Block,
    ClassDefinition,
	ClassLiteral,
	ClassMethodAssignment,
	ClassVariable,
    Conditional,
	ConstantAssignment,
    DirectOperand,
	ExternLabel,
	FalseLiteral,
    FunctionCall,
    FunctionDef,
    HashOperand,
	ImmediateOperand,
    IndirectOperand,
	IndirectOperandTerm,
    InlineAssembly,
    Instruction,
    IntegerLiteral,
    Label,
	MethodAssignment,
    MutableAssignment,
	NullLiteral,
    ObjectOperand,
	Parameter,
    ParameterDef,
    ReturnStatement,
	Self,
    SourceFile,
	StringLiteral,
	TrueLiteral,
	Variable
  };

  ASTNode();
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

  ASTNode* MutableFindEnclosingNode(const std::string&);
  const ASTNode *FindEnclosingNode(const std::string&) const;

  virtual void Analyse( Scope* );
  virtual AssemblyBlock* GenerateCode() { return new AssemblyBlock(); }
  virtual AssemblyBlock* GetAuxiliaryCode();
  virtual AssemblyBlock* PushOntoStack() { return new AssemblyBlock(); }

  virtual std::string Print() const { return "Unimplemented"; }

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

std::ostream& operator<<(std::ostream&, const ASTNode&);

#include "ast/operand_node.h"

// Include the derived classes here for convenience
#include "ast/address_operand_node.h"
#include "ast/assignment_target_node.h"
#include "ast/block_node.h"
#include "ast/class_definition_node.h"
#include "ast/class_literal_node.h"
#include "ast/class_method_assignment_node.h"
#include "ast/class_variable_node.h"
#include "ast/conditional_node.h"
#include "ast/constant_assignment_node.h"
#include "ast/direct_operand_node.h"
#include "ast/extern_label_node.h"
#include "ast/false_literal_node.h"
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
#include "ast/true_literal_node.h"
#include "ast/variable_node.h"

#endif
