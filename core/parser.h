#ifndef PARSER_H
#define PARSER_H

#include <list>

class ASTNode;

// For these macros, INT denotes "intermediate", for matcher functions which 
// don't return a final ASTNode for inclusion in the AST. These functions return
// a base ASTNode, rather than a specific ASTBlockNode etc

#define MATCHER_PROTOTYPE_FOR(name) AST##name##Node *Match##name()
#define INT_MATCHER_PROTOTYPE_FOR(name) ASTNode *Match##name();

#define MATCHER_FOR(name) AST##name##Node *Parser::Match##name()
#define INT_MATCHER_FOR(name) ASTNode *Parser::Match##name() // For interim parser functions that don't produce a specific derived ASTNode

#define MATCH(name) Match##name()

typedef std::list<Token>::iterator TokenIterator;

class Parser {
  friend class ParserTest;
 public:
  Parser( std::list<Token> &tokenStream) { currentToken = tokenStream.begin(); endToken = tokenStream.end(); }
  ASTNode *Parse();
  ASTNode *MatchExpression();
  FunctionDefNode *MatchFunctionDef();
  FunctionCallNode *MatchFunctionCall();
  ParameterNode *MatchParameter();
  ParameterDefNode *MatchParameterDef();
  ASTNode *MatchStatement();
  BlockNode *MatchBlock();
  ASTNode *MatchAssignment();
  MutableAssignmentNode *MatchMutableAssignment();
  ImmutableAssignmentNode *MatchImmutableAssignment();
  ConditionalNode *MatchConditional();
  FunctionCallNode *MatchMethodInvocation();
  ASTNode *MatchReceiver();
  ReturnStatementNode *MatchReturnStatement();
  MATCHER_PROTOTYPE_FOR( ClassDefinition ); 
  // Assembly Language Matchers
  InlineAssemblyNode * MatchInlineAssembly();
  InstructionNode* MatchInstruction();
  OperandNode *MatchOperand();
  DirectOperandNode *MatchDirectOperand();
  ImmediateOperandNode *MatchImmediateOperand();
  ObjectOperandNode *MatchObjectOperand();
  HashOperandNode *MatchHashOperand();
  MATCHER_PROTOTYPE_FOR( IndirectOperand );
  MATCHER_PROTOTYPE_FOR( IndirectOperandTerm );
  void ConsumeToken() { currentToken++; }
  void ResetTokenPosition( TokenIterator savedCurr ) { currentToken = savedCurr; }
  int CurrentSourcePosition() { return currentToken->LineNumber(); }
  bool TokenIs( TokenType type );
  bool TokenIsNot( TokenType type );
  bool LookAheadFor( TokenType type );
 private:
  TokenIterator currentToken;
  TokenIterator endToken;
};

#endif
