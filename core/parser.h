#ifndef PARSER_H
#define PARSER_H

#include "token.hpp"

class ASTNode;

// For these macros, INT denotes "intermediate", for matcher functions which
// don't return a final ASTNode for inclusion in the AST. These functions return
// a base ASTNode, rather than a specific ASTBlockNode etc

#define MATCHER_PROTOTYPE_FOR(name) AST##name##Node *Match##name()
#define INT_MATCHER_PROTOTYPE_FOR(name) ASTNode *Match##name();

#define MATCHER_FOR(name) AST##name##Node *Parser::Match##name()
#define INT_MATCHER_FOR(name) ASTNode *Parser::Match##name() // For interim parser functions that don't produce a specific derived ASTNode

#define MATCH(name) Match##name()

class Parser {
  friend class ParserTest;
  friend class AssemblyParserTest;
 public:
  Parser(::SourceFile*);
  ASTNode *Parse( ASTNode* );
  ASTNode *MatchExpression();
  FunctionDefNode *MatchFunctionDef();
  FunctionCallNode *MatchFunctionCall();
  ParameterNode *MatchParameter();
  ParameterDefNode *MatchParameterDef();
  ASTNode *MatchStatement();
  ASTNode *MatchIncludeStatement();
  BlockNode *MatchBlock();
  ASTNode *MatchAssignment();
  MutableAssignmentNode *MatchMutableAssignment();
  ConstantAssignmentNode *MatchConstantAssignment();
  AssignmentTargetNode *MatchAssignmentTarget();
  ConditionalNode *MatchConditional();
  FunctionCallNode *MatchMethodInvocation();
  ASTNode *MatchReceiver();
  ReturnStatementNode *MatchReturnStatement();

  // Class declarations
  ClassDefinitionNode *MatchClassDefinition();
  MethodAssignmentNode *MatchMethodAssignment();
  ClassMethodAssignmentNode *MatchClassMethodAssignment();
  // Assembly Language Matchers
  InlineAssemblyNode * MatchInlineAssembly();
  InstructionNode* MatchInstruction();
  OperandNode *MatchOperand();
  OperandNode *MatchModifiedOperand();
  DirectOperandNode *MatchDirectOperand();
  ImmediateOperandNode *MatchImmediateOperand();
  ObjectOperandNode *MatchObjectOperand();
  HashOperandNode *MatchHashOperand();
  AddressOperandNode *MatchAddressOperand();
  IndirectOperandNode *MatchIndirectOperand();
  IndirectOperandTermNode *MatchIndirectOperandTerm();
  ExternLabelNode *MatchExternLabel();
  void ConsumeToken() { currentToken++; }
  void ResetTokenPosition( TokenIterator savedCurr ) { currentToken = savedCurr; }
  int CurrentSourcePosition() { return currentToken->LineNumber(); }
  bool TokenIs( TokenType type );
  bool TokenIsNot( TokenType type );
  bool LookAheadFor( TokenType type );
 private:
  ::SourceFile *sourceFile;
  TokenIterator currentToken;
  TokenIterator endToken;
};

#endif
