#ifndef PARSER_H
#define PARSER_H

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
 public:
  Parser( struct _Token *tokenStream ) { currentToken = tokenStream; }
  ASTNode *parse();
  INT_MATCHER_PROTOTYPE_FOR( Expression );
  MATCHER_PROTOTYPE_FOR( FunctionDef );
  MATCHER_PROTOTYPE_FOR( FunctionCall );
  MATCHER_PROTOTYPE_FOR( Parameter );
  MATCHER_PROTOTYPE_FOR( ParameterDef );
  INT_MATCHER_PROTOTYPE_FOR( Statement );
  MATCHER_PROTOTYPE_FOR( Block );
  INT_MATCHER_PROTOTYPE_FOR( Assignment );
  MATCHER_PROTOTYPE_FOR( MutableAssignment );
  MATCHER_PROTOTYPE_FOR( ImmutableAssignment );
  MATCHER_PROTOTYPE_FOR( Conditional );
  ASTFunctionCallNode *MatchMethodInvocation();
  INT_MATCHER_PROTOTYPE_FOR( Receiver );
  MATCHER_PROTOTYPE_FOR( ReturnStatement );
  MATCHER_PROTOTYPE_FOR( ClassDefinition );
  void ConsumeToken() { currentToken = currentToken->next; }
  void ResetTokenPosition( struct _Token *savedCurr ) { currentToken = savedCurr; }
  int CurrentSourcePosition() { return currentToken->line_no; }
  bool TokenIs( enum TOKEN_TYPE type) { return currentToken && currentToken->type == type; }
  bool TokenIsNot( enum TOKEN_TYPE type) { return !currentToken || currentToken->type != type; }
  bool LookAheadFor( enum TOKEN_TYPE type );
 private:
  struct _Token *currentToken;
};

#endif
