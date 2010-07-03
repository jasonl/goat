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
  INT_MATCHER_PROTOTYPE_FOR( Expression );
  FunctionDefNode *MatchFunctionDef();
  FunctionCallNode *MatchFunctionCall();
  ParameterNode *MatchParameter();
  ParameterDefNode *MatchParameterDef();
  INT_MATCHER_PROTOTYPE_FOR( Statement );
  BlockNode *MatchBlock();
  INT_MATCHER_PROTOTYPE_FOR( Assignment );
  MATCHER_PROTOTYPE_FOR( MutableAssignment );
  ImmutableAssignmentNode *MatchImmutableAssignment();
  ConditionalNode *MatchConditional();
  FunctionCallNode *MatchMethodInvocation();
  INT_MATCHER_PROTOTYPE_FOR( Receiver );
  ReturnStatementNode *MatchReturnStatement();
  MATCHER_PROTOTYPE_FOR( ClassDefinition ); 
  // Assembly Language Matchers
  InlineAssemblyNode * MatchInlineAssembly();
  InstructionNode* MatchInstruction();
  OperandNode *MatchOperand();
  DirectOperandNode *MatchDirectOperand();
  ImmediateOperandNode *MatchImmediateOperand();
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
