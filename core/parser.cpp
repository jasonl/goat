/*
 * ast.c
 *
 * A recursive-descent parser for the Goat language
 *
 * Grammar (EBNF)
 * -----------------------------------------------------------------------------
 * block                 = indent_increase,{ statement_group }, indent_decrease;
 * statement_group       = statement, { statement }
 * statement             = [ assignment | function_call | conditional | class_def | return_statement], newline;
 *
 * assignment            = mutable_assignment | immutable_assignment;
 * mutable_assignment    = identifier, equals, expression;
 * immutable_assignment  = identifier, colon, expression;
 *
 * conditional           = if, expression, newline, block, [ else, newline, block ];
 *
 * return_statement      = return, [expression];
 *
 * (* Class Definition *)
 * class_def             = class, identifier, indent_increase, { assignment }, indent_decrease
 *
 * (* An expression is something which evaluates to an object: In the case of
 * a function, it evaluates to a function object *)
 * expression            = identifier | integer | string | function_definition | function_call;
 *
 * (* Function definitions *)
 * function_definition   = one_line_func_def | block_func_def;
 * one_line_func_def     = lambda, left_paren, { parameter_def, { comma, parameter_def}}, hash_rocket, statement, right_paren;
 * block_func_def        = lambda, left_paren, {parameter_def, {comma, parameter_def}}, right_paren, block;
 * parameter_def         = identifier; [Todo: Add Named Parameters]
 *
 * (* Function calls *)
 * function_call         = [receiver], method_invocation;
 * method_invocation     = [period] identifier, [left_paren] , { parameter }, [right_paren];
 * receiver              = method_invocation | string_literal | integer_literal | identifier ;
 * 
 * parameter             = named_parameter | expression;
 * named_parameter       = identifier, colon, expression;
 *
 * (* Lexical tokens *)
 * (* defined here for completeness, but the tokenizing is done in lexer.c *)
 * integer               = [ "-" ], digit, { digit };
 * comma                 = ",";
 * period                = ".";
 * semicolon             = ";";
 * right_paren           = "(";
 * left_paren            = ")";
 * equals                = "=";
 * lambda                = "λ";
 * digit                 = "0" - "9"
 *
 */
#include <string.h>
#include <string>
#include "lexer.h"
#include "ast_node.h"
#include "parser.h"
#include "goat.h"

const char *TOKEN_TYPES[]={"Whitespace", "Indent", "Comment", "NewLine", "Identifier",
			   "RightParen", "LeftParen", "Lambda", "Colon", "Period", "Comma",
			   "Equals", "End", "Integer", "String", "If", "Else", "Class", "Return", "HashRocket",
			   "IndentIncrease", "IndentDecrease", "End of File"};

ASTNode * Parser::parse() {
  ASTNode *astRoot = new ASTNode( ASTNode::SourceFile );
  ASTNode *newChild;

  // Remove any leading newlines - e.g. from comments
  // The lexer includes a newline token after a comment
  while( TokenIs( Newline )) {
    ConsumeToken();
  }


  while((newChild = MATCH(Statement))) {
    if( TokenIs( Newline )) {
      ConsumeToken();
      astRoot->append(newChild);
      
      // Ignore any blank links
      while( TokenIs( Newline )) {
	ConsumeToken();
      }

    } else if( TokenIs( EndOfFile)) {
      return astRoot;
    } else {
      // Found something on a line we couldn't match
      goatError(CurrentSourcePosition(), "Unexpected token %s[%s] found.", TOKEN_TYPES[currentToken->type], currentToken->content);
      delete astRoot;
      return NULL;
    }
  }

  return astRoot;
}

// Helper function to perform look-aheads in the token stream
// where we need to resolve ambiguities.
bool Parser::LookAheadFor( enum TOKEN_TYPE token_type) {
  if(currentToken->next == NULL) return FALSE;

  return currentToken->next->type == token_type;
}

// Matches a block - a group of statements with a common indent
MATCHER_FOR( Block ) {
  ASTNode *newChild = NULL, *thisNode = NULL;
    
  if(!currentToken) { return NULL; }

  if(TokenIsNot( IndentIncrease )) { return NULL; }
  ConsumeToken();

  thisNode = new ASTBlockNode();

  // Match at least one statement
  if((newChild = MATCH(Statement))) {
    if( TokenIs( Newline )) {
      ConsumeToken();
      thisNode->append(newChild);
      
      // Ignore any blank links
      while( TokenIs( Newline )) {
	ConsumeToken();
      }
    } else {
      // Found something on a line we couldn't match
      goatError(CurrentSourcePosition(), "Unexpected token %s[%s] found.", TOKEN_TYPES[currentToken->type], currentToken->content);
      delete thisNode;
      return 0;
    }
  }
  else {
    goatError(CurrentSourcePosition(), "Could not match a statement in block");
    delete thisNode;
    return NULL;
  }

  while((newChild = MATCH(Statement))) {
    if( TokenIs( Newline )) {
      ConsumeToken();
      thisNode->append( newChild );
      
      // Ignore any blank links
      while( TokenIs( Newline )) {
	ConsumeToken();
      }
    } else {
      // Found something on a line we couldn't match
      goatError(CurrentSourcePosition(), "Unexpected token %s[%s] found.", TOKEN_TYPES[currentToken->type], currentToken->content);
      delete thisNode;
      return 0;
    }  
  }

  if( TokenIsNot( IndentDecrease )) {
    goatError(CurrentSourcePosition(), "Invalid token %s found in block.", TOKEN_TYPES[currentToken->type]);
    delete thisNode;
    return NULL;
  }
    
  ConsumeToken();
  return thisNode;
}

MATCHER_FOR( Statement ) 
{
  ASTNode *thisNode;

  if((thisNode = MATCH( Assignment )) || 
     (thisNode = MATCH( FunctionCall )) || 
     (thisNode = MATCH( Conditional )) ||
     (thisNode = MATCH( ReturnStatement))) {   
    return thisNode;
  }

  return NULL;
}

// Match an expression
MATCHER_FOR( Expression ) {
  Token *savedCurr = currentToken;
  ASTNode *thisNode = NULL;

  if((thisNode = MATCH( FunctionCall ))) {
    return thisNode;
  }
  
  if( TokenIs( LeftParen )) {
    ConsumeToken();
    if((thisNode = MATCH(Expression))) {
      if( TokenIs( RightParen)) {
	ConsumeToken();
	return thisNode;
      } 
      else {
	goatError(CurrentSourcePosition(), "Expression: expected to find a right parenthesis, found a %s instead.", TOKEN_TYPES[currentToken->type]);
	ResetTokenPosition( savedCurr );
	return NULL;
      }
    }
  }

  if((thisNode = MATCH( FunctionDef ))) {
    return thisNode;
  }
  
  if( TokenIs( String ) ) {
    thisNode = new ASTNode( ASTNode::StringLiteral );
    thisNode->token = currentToken;
    ConsumeToken();
    return thisNode;
  }

  if( TokenIs( Integer )) {
    thisNode = new ASTNode( ASTNode::IntegerLiteral );
    thisNode->token = currentToken;
    ConsumeToken();
    return thisNode;
  }

  if( TokenIs( Identifier )) {
    thisNode = new ASTNode( ASTNode::Variable );
    thisNode->token = currentToken;
    ConsumeToken();
    return thisNode;
  }

  return NULL;
}

// Matches an object which a function call can be made to
MATCHER_FOR( Receiver ) {
  Token *savedCurr = currentToken;
  ASTNode *thisNode = NULL;

  if (TokenIs( LeftParen )) {
    ConsumeToken();
    if ((thisNode = MATCH(Expression))) {
      if (TokenIs( RightParen)) {
	ConsumeToken();
	return thisNode;
      } 
      else {
	goatError(CurrentSourcePosition(), "Receiver: expected to find a right parenthesis, found a %s instead.", TOKEN_TYPES[currentToken->type]);
	ResetTokenPosition( savedCurr );
	return NULL;
      }
    }
    ResetTokenPosition( savedCurr );
    return NULL;
  }

  if( TokenIs( Identifier )) {
    // Lookahead to determine if this identifier is actually
    // a receiver or a method name
    if (!LookAheadFor( LeftParen )) {
      thisNode = new ASTNode( ASTNode::Variable );
      thisNode->token = currentToken;
      ConsumeToken();
      return thisNode;
    }
  }

  if (TokenIs( String ) ) {
    thisNode = new ASTNode( ASTNode::StringLiteral );
    thisNode->token = currentToken;
    ConsumeToken();
    return thisNode;
  }

  if (TokenIs( Integer )) {
    thisNode = new ASTNode( ASTNode::IntegerLiteral );
    thisNode->token = currentToken;
    ConsumeToken();
    return thisNode;
  }

  return NULL;
}

MATCHER_FOR( FunctionCall ) {
  ASTNode *thisNode = NULL, *receiver = NULL, *newParent = NULL;
  Token *savedCurr = currentToken;

  receiver = MATCH( Receiver );
  
  if(!(thisNode = MATCH( MethodInvocation ))) {
    ResetTokenPosition( savedCurr );
    if(receiver) delete receiver;
    return NULL;
  }

  if( receiver ) {
    thisNode->InsertFirstChild(receiver);
  }

  while((newParent = MATCH( MethodInvocation ))) {    
    newParent->InsertFirstChild( thisNode );
    thisNode = newParent;
  }

  return thisNode;
}

MATCHER_FOR( MethodInvocation ) {
  Token *functionName, *savedCurr = currentToken;
  ASTNode *thisNode = NULL, *newChild = NULL;
  int must_match = FALSE, must_match_paren = FALSE;

  // optional period for method calls.
  if (TokenIs( Period )) {
    ConsumeToken();
  }

  if (TokenIsNot( Identifier )) { 
    ResetTokenPosition( savedCurr );
    return NULL; 
  }
  
  functionName = currentToken;
  ConsumeToken();

  if (TokenIs( LeftParen )) {
    ConsumeToken();
    must_match_paren = TRUE;
  }
 
  thisNode = new ASTNode( ASTNode::FunctionCall );

  // We don't append the receiver here - that's done in astMatchFunctionCall
  thisNode->token = functionName;

  while((newChild = MATCH( Parameter ))) {
    thisNode->append(newChild);

    // So if we match a right Parenthesis, that's a complete function call
    if (TokenIs( RightParen ) && must_match_paren ) {
      ConsumeToken();
      return thisNode;
    }

    // If we match a comma, then we must match another parameter.
    if (TokenIs( Comma )) {
      must_match = TRUE;
      ConsumeToken();
      continue;
    }

    if ( !must_match ) {
      // We've found some other token that doesn't match as a comma or right_paren
      return thisNode;
    }

    // If execution gets to here, we've encountered some other token
    goatError(CurrentSourcePosition(), "MethodInvocation: Unexpected %s found when a right parenthesis ')' was expected.", TOKEN_TYPES[currentToken->type]);
    delete thisNode;
    return NULL;
  }
  
  if( !must_match ) {
    if (TokenIs( RightParen )) {
      if( must_match_paren ) {
	ConsumeToken();
	return thisNode;
      } else {
	// Don't consume the token, try to match it as part of an expression
	return thisNode;
      }
    } else {
      if( must_match_paren ) {
	goatError(CurrentSourcePosition(), "Could not find Right Paren to close function call parsing");
	delete thisNode;
	return NULL;
      } else {
	// Leave the token, try to match it with the next node
	return thisNode;
      }
    }
  } else {
    goatError(CurrentSourcePosition(), "Another function parameter expected after comma; none was matched.");
    delete thisNode;
    return NULL;
  }
}

MATCHER_FOR( FunctionDef ) {
  ASTNode *thisNode, *newChild;
  Token *savedCurr = currentToken;
  int must_match = FALSE;


  if( TokenIsNot( Lambda )) { return NULL; }
  ConsumeToken();

  if( TokenIsNot( LeftParen )) {
    goatError(CurrentSourcePosition(), "Unexpected %s found when a left parenthesis '(' was expected.", TOKEN_TYPES[currentToken->type]);
    ResetTokenPosition( savedCurr );
    return NULL; 
  }
  ConsumeToken();
  
  thisNode = new ASTNode( ASTNode::FunctionDef );

  while((newChild = MATCH( ParameterDef ))) {
    thisNode->append(newChild);
    
    // So if we match a right Parenthesis, that's a complete function call
    if( TokenIs( RightParen )) {
      break;
    }
    
    // If we match a comma, then we must match another parameter.
    if( TokenIs( Comma ) && ! must_match) {
      must_match = TRUE;
      ConsumeToken();
      continue;
    }
    
    // If execution gets to here, we've encountered some other token
    goatError(CurrentSourcePosition(), "FunctionDefinition: Unexpected %s found when a right parenthesis ')' was expected.", TOKEN_TYPES[currentToken->type]);
    delete thisNode;
    return NULL;
  }

  if( TokenIsNot( RightParen)) {
    goatError(CurrentSourcePosition(), "FunctionDefinition: Unexpected %s found when a right parenthesis ')' was expected.", TOKEN_TYPES[currentToken->type]);
    delete thisNode;
    return NULL;
  }
  ConsumeToken();

  if (TokenIsNot( Newline )) {
    goatError(CurrentSourcePosition(), "FunctionDefinition: Unexpected %s found when a Newline was expected.", TOKEN_TYPES[currentToken->type]);
    delete thisNode;
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  ConsumeToken();
  
  if ((int)(newChild = MATCH( Block ))) {
    thisNode->append(newChild);
    return thisNode;  
  } else {
    goatError(CurrentSourcePosition(), "No Block found for function definition");
    delete thisNode;
    ResetTokenPosition( savedCurr );
    return NULL;
  }
}

MATCHER_FOR( ParameterDef ) {
  ASTNode *thisNode;

  if (TokenIs( Identifier )) {
    thisNode = new ASTNode( ASTNode::ParameterDef );
    thisNode->token = currentToken;
    ConsumeToken();
    return thisNode;
  } else {
    return NULL;
  }
}

MATCHER_FOR( Parameter ) {
  ASTNode *thisNode, *newChild;

  //TODO: Add matching for named parameters
  if(( newChild = MATCH( Expression ))) {
    thisNode = new ASTNode( ASTNode::Parameter );
    thisNode->append(newChild);
    return thisNode;
  }
  
  return NULL;
}

MATCHER_FOR( Conditional ) {
  ASTNode *thisNode, *exprChild, *ifChild, *elseChild;
  Token *savedCurr = currentToken;

  if (TokenIsNot( If )) { return NULL; }
  thisNode = new ASTNode( ASTNode::Conditional );
  ConsumeToken();

  if (!(int)(exprChild = MATCH( Expression))) {
    delete thisNode;
    ResetTokenPosition( savedCurr );
    goatError(CurrentSourcePosition(), "Unexpected token %s found after if keyword.", TOKEN_TYPES[currentToken->type]);
    return NULL;
  }
  thisNode->append(exprChild);

  if (TokenIsNot( Newline )) {
    delete thisNode;
    ResetTokenPosition( savedCurr );
    goatError(CurrentSourcePosition(), "Unexpected token %s found after if-expression; should be a new line.", TOKEN_TYPES[currentToken->type]);
    return NULL;
  }
  ConsumeToken();

  // Match the block to be run if the condition executes to true
  if(!(int)(ifChild = MATCH( Block ))) {
    goatError(CurrentSourcePosition(), "Unexpected token %s found after if keyword.", TOKEN_TYPES[currentToken->type]);
    delete thisNode;
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  thisNode->append(ifChild);

  if (TokenIsNot( Else ) ) {
    // So no else clause
    return thisNode;
  }
  ConsumeToken();

  if (TokenIsNot( Newline )) {
    delete thisNode;
    ResetTokenPosition( savedCurr );
    goatError(CurrentSourcePosition(), "Unexpected token %s found after else-expression; should be a new line.", TOKEN_TYPES[currentToken->type]);
    return NULL;
  }
  ConsumeToken();

  if (!(elseChild = MATCH( Block ))) {
    goatError(CurrentSourcePosition(), "Unexpected token %s found after else keyword.", TOKEN_TYPES[currentToken->type]);
    delete thisNode;
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  thisNode->append(elseChild);
  return thisNode;
}


MATCHER_FOR( Assignment ) {
  ASTNode *thisNode;
  if((thisNode = MATCH( ImmutableAssignment ))) {
    return thisNode;
  }

  if((thisNode = MATCH( MutableAssignment ))) {
    return thisNode;
  }

  return NULL;
}

MATCHER_FOR( MutableAssignment ) {
  Token *variable, *savedCurr = currentToken;
  ASTNode *newChild = NULL, *thisNode = NULL;
  
  if(TokenIsNot( Identifier)) { return NULL; }
  variable = currentToken;
  ConsumeToken();
  
  if(TokenIsNot( Equals )) {
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  ConsumeToken();
  
  if((newChild = MATCH( Expression ))) {
    thisNode = new ASTNode( ASTNode::MutableAssignment );
    thisNode->token = variable;
    thisNode->append(newChild);
    return thisNode;
  }
  
  goatError(CurrentSourcePosition(), "Unexpected token %s found after equals sign in a mutable assignment.", TOKEN_TYPES[currentToken->type]);
  ResetTokenPosition( savedCurr );
  return NULL;
}

MATCHER_FOR( ImmutableAssignment ) {
  Token *variable, *savedCurr = currentToken;
  ASTNode *newChild = NULL, *thisNode = NULL;
  
  if(TokenIsNot( Identifier)) { return NULL; }
  variable = currentToken;
  ConsumeToken();
  
  if(TokenIsNot( Colon )) {
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  ConsumeToken();
  
  if((newChild = MATCH( Expression ))) {
    thisNode = new ASTNode( ASTNode::ImmutableAssignment );
    thisNode->token = variable;
    thisNode->append(newChild);
    return thisNode;
  }
  
  goatError(CurrentSourcePosition(), "Unexpected token %s found after colon sign in a immutable assignment.", TOKEN_TYPES[currentToken->type]);
  ResetTokenPosition( savedCurr );
  return NULL;
}

MATCHER_FOR( ReturnStatement ) {
  ASTNode *thisNode, *returnExpr;

  if( TokenIsNot( Return )) {
    return NULL;
  }
  ConsumeToken();

  thisNode = new ASTNode( ASTNode::ReturnStatement );

  if(!(returnExpr = MATCH( Expression ))){
    returnExpr = new ASTNode( ASTNode::NullLiteral );
  }
  
  thisNode->append(returnExpr);
  return thisNode;
}

MATCHER_FOR( ClassDefinition ) {
  ASTNode *thisNode, *newNode;
  Token *savedCurr = currentToken;

  if( TokenIsNot( Class )) {
    return NULL;
  }
  ConsumeToken();

  if( TokenIs( Identifier )) {
    thisNode = new ASTNode( ASTNode::ClassDefinition );
    thisNode->token = currentToken;
  } else {
    goatError(CurrentSourcePosition(), "Unexpected token %s found after class keyword. Identifier expected", TOKEN_TYPES[currentToken->type]);
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  ConsumeToken();
  
  if( TokenIsNot( Newline )) {
    goatError(CurrentSourcePosition(), "Unexpected token %s found after class name. Newline expected", TOKEN_TYPES[currentToken->type]);
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  ConsumeToken();


  if( TokenIsNot( IndentIncrease )) {
    // Empty class
    return thisNode;
  }
  ConsumeToken();

  while((newNode = MATCH(Assignment))) {
    thisNode->append(newNode);
    if( TokenIs( Newline )) {
      ConsumeToken();
    } else {
      goatError(CurrentSourcePosition(), "Unexpected token %s found in class definition block. Could not match assignment", TOKEN_TYPES[currentToken->type]);
      ResetTokenPosition( savedCurr );
      return NULL;
    }
  }

  if( TokenIs( IndentDecrease )) {
    ConsumeToken();
    return thisNode;
  } else {
    goatError(CurrentSourcePosition(), "Unexpected token %s found when indent decrease to close class definition block expected.", TOKEN_TYPES[currentToken->type]);
    delete thisNode;
    ResetTokenPosition( savedCurr );
    return NULL;
  }
}
