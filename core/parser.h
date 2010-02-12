#ifndef PARSER_H
#define PARSER_H

class ASTNode;

#define MATCHER_PROTOTYPE_FOR(name) ASTNode *Match##name()
#define MATCH(name) Match##name()

class Parser {
  friend class ParserTest;
 public:
  Parser( struct _Token *tokenStream ) { currentToken = tokenStream; }
  ASTNode *parse();
  MATCHER_PROTOTYPE_FOR( Expression );
  MATCHER_PROTOTYPE_FOR( FunctionDef );
  MATCHER_PROTOTYPE_FOR( FunctionCall );
  MATCHER_PROTOTYPE_FOR( Parameter );
  MATCHER_PROTOTYPE_FOR( ParameterDef );
  MATCHER_PROTOTYPE_FOR( Statement );
  MATCHER_PROTOTYPE_FOR( Block );
  MATCHER_PROTOTYPE_FOR( Assignment );
  MATCHER_PROTOTYPE_FOR( MutableAssignment );
  MATCHER_PROTOTYPE_FOR( ImmutableAssignment );
  MATCHER_PROTOTYPE_FOR( Conditional );
  MATCHER_PROTOTYPE_FOR( MethodInvocation );
  MATCHER_PROTOTYPE_FOR( Receiver );
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
