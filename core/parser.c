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
#include <malloc.h>
#include <string.h>
#include "lexer.h"
#include "ast.h"
#include "goat.h"

const char *TOKEN_TYPES[]={"Whitespace", "Indent", "Comment", "NewLine", "Identifier",
			   "RightParen", "LeftParen", "Lambda", "Colon", "Period", "Comma",
			   "Equals", "End", "Integer", "String", "If", "Else", "Class", "Return", "HashRocket",
			   "IndentIncrease", "IndentDecrease", "End of File"};

int goatBuildAST( GoatState *G ) {
  Node *astRoot = astCreateNode( SourceFile );
  Node *newChild;

  Token *source = G->tokens;
  Token **curr = &source;  

  // Remove any leading newlines - e.g. from comments
  // The lexer includes a newline token after a comment
  while( TOKEN_IS_A( Newline )) {
    CONSUME_TOKEN;
  }


  while((newChild = MATCH(Statement))) {
    if( TOKEN_IS_A( Newline )) {
      CONSUME_TOKEN;
      astAppendChild( newChild, astRoot );
      
      // Ignore any blank links
      while( TOKEN_IS_A( Newline )) {
	CONSUME_TOKEN;
      }

    } else if( TOKEN_IS_A( EndOfFile)) {
      G->astRoot = astRoot;
      return 1;
    } else {
      // Found something on a line we couldn't match
      goatError((*curr)->line_no, "Unexpected token %s[%s] found.", TOKEN_TYPES[(*curr)->type], (*curr)->content);
      astFreeNode(astRoot);
      return 0;
    }
  }

  G->astRoot = astRoot;
  return 1;
}



// Matches a block - a group of statements with a common indent
MATCHER_FOR( Block ) {
  Node *newChild = NULL, *thisNode = NULL;
    
  if(!(*curr)) { return NULL; }

  if(TOKEN_IS_NOT_A( IndentIncrease )) { return NULL; }
  CONSUME_TOKEN;

  thisNode = astCreateNode( Block );

  // Match at least one statement
  if((newChild = MATCH(Statement))) {
    if( TOKEN_IS_A( Newline )) {
      CONSUME_TOKEN;
      astAppendChild( newChild, thisNode );
      
      // Ignore any blank links
      while( TOKEN_IS_A( Newline )) {
	CONSUME_TOKEN;
      }
    } else {
      // Found something on a line we couldn't match
      goatError((*curr)->line_no, "Unexpected token %s[%s] found.", TOKEN_TYPES[(*curr)->type], (*curr)->content);
      astFreeNode(thisNode);
      return 0;
    }
  }
  else {
    goatError((*curr)->line_no, "Could not match a statement in block");
    astFreeNode(thisNode);
    return NULL;
  }

  while((newChild = MATCH(Statement))) {
    if( TOKEN_IS_A( Newline )) {
      CONSUME_TOKEN;
      astAppendChild( newChild, thisNode );
      
      // Ignore any blank links
      while( TOKEN_IS_A( Newline )) {
	CONSUME_TOKEN;
      }
    } else {
      // Found something on a line we couldn't match
      goatError((*curr)->line_no, "Unexpected token %s[%s] found.", TOKEN_TYPES[(*curr)->type], (*curr)->content);
      astFreeNode(thisNode);
      return 0;
    }  
  }

  if( TOKEN_IS_NOT_A( IndentDecrease )) {
    goatError((*curr)->line_no, "Invalid token %s found in block.", TOKEN_TYPES[(*curr)->type]);
    astFreeNode( thisNode );
    return NULL;
  }
    
  CONSUME_TOKEN;
  return thisNode;
}

MATCHER_FOR( Statement ) 
{
  Node *thisNode;

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
  Token *saved_curr = *curr;
  Node *thisNode = NULL;

  if((thisNode = MATCH( FunctionCall ))) {
    return thisNode;
  }
  
  if( TOKEN_IS_A( LeftParen )) {
    CONSUME_TOKEN;
    if((thisNode = MATCH(Expression))) {
      if( TOKEN_IS_A( RightParen)) {
	CONSUME_TOKEN;
	return thisNode;
      } 
      else {
	goatError((*curr)->line_no, "Expression: expected to find a right parenthesis, found a %s instead.", TOKEN_TYPES[(*curr)->type]);
	(*curr) = saved_curr;
	return NULL;
      }
    }
  }

  if((thisNode = MATCH( FunctionDef ))) {
    return thisNode;
  }
  
  if( TOKEN_IS_A( String ) ) {
    RETURN_TERMINAL_NODE( StringLiteral );
  }

  if( TOKEN_IS_A( Integer )) {
    RETURN_TERMINAL_NODE( IntegerLiteral );
  }

  if( TOKEN_IS_A( Identifier )) {
    RETURN_TERMINAL_NODE( Variable );
  }

  return NULL;
}

// Matches an object which a function call can be made to
MATCHER_FOR( Receiver ) {
  Token *saved_curr = *curr;
  Node *thisNode = NULL;

  if( TOKEN_IS_A( LeftParen )) {
    CONSUME_TOKEN;
    if((thisNode = MATCH(Expression))) {
      if( TOKEN_IS_A( RightParen)) {
	CONSUME_TOKEN;
	return thisNode;
      } 
      else {
	goatError((*curr)->line_no, "Receiver: expected to find a right parenthesis, found a %s instead.", TOKEN_TYPES[(*curr)->type]);
	(*curr) = saved_curr;
	return NULL;
      }
    }
  }

  if( TOKEN_IS_A( Identifier )) {
    // Lookahead to determine if this identifier is actually
    // a receiver or a method name
    if(!astLookaheadFor( curr, LeftParen)) {
      RETURN_TERMINAL_NODE( Variable );
    }
  }

  if( TOKEN_IS_A( String ) ) {
    RETURN_TERMINAL_NODE( StringLiteral );
  }

  if( TOKEN_IS_A( Integer )) {
    RETURN_TERMINAL_NODE( IntegerLiteral );
  }

  return NULL;
}

MATCHER_FOR( FunctionCall ) {
  Token *savedcurr = *curr;
  Node *thisNode = NULL, *receiver = NULL, *newParent = NULL;

  receiver = MATCH( Receiver );
  
  if(!(thisNode = MATCH( MethodInvocation ))) {
    (*curr) = savedcurr;
    if(receiver) astFreeNode(receiver);
    return NULL;
  }

  if( receiver ) {
    astInsertFirstChild( receiver, thisNode);
  }

  while((newParent = MATCH( MethodInvocation ))) {    
    astInsertFirstChild( thisNode, newParent );
    thisNode = newParent;
  }

  return thisNode;
}

MATCHER_FOR( MethodInvocation ) {
  Token *savedcurr = *curr, *functionName;
  Node *thisNode = NULL, *newChild = NULL;
  int must_match = FALSE, must_match_paren = FALSE;

  // optional period for method calls.
  if( TOKEN_IS_A( Period )) { CONSUME_TOKEN; }

  if( TOKEN_IS_NOT_A( Identifier )) { 
    *curr = savedcurr;
    return NULL; 
  }
  
  functionName = (*curr);
  CONSUME_TOKEN;

  if( TOKEN_IS_A( LeftParen )) {
    CONSUME_TOKEN;
    must_match_paren = TRUE;
  }
 
  thisNode = astCreateNode( FunctionCall );

  // We don't append the receiver here - that's done in astMatchFunctionCall
  thisNode->token = functionName;

  while((newChild = MATCH( Parameter ))) {
    astAppendChild(newChild, thisNode);

    // So if we match a right Parenthesis, that's a complete function call
    if( TOKEN_IS_A( RightParen ) && must_match_paren ) {
      CONSUME_TOKEN;
      return thisNode;
    }

    // If we match a comma, then we must match another parameter.
    if( TOKEN_IS_A( Comma )) {
      must_match = TRUE;
      CONSUME_TOKEN;
      continue;
    }

    if( ! must_match ) {
      // We've found some other token that doesn't match as a comma or right_paren
      return thisNode;
    }

    // If execution gets to here, we've encountered some other token
    goatError((*curr)->line_no, "MethodInvocation: Unexpected %s found when a right parenthesis ')' was expected.", TOKEN_TYPES[(*curr)->type]);
    astFreeNode( thisNode );
    return NULL;
  }
  
  if( !must_match ) {
    if (TOKEN_IS_A( RightParen )) {
      if( must_match_paren ) {
	CONSUME_TOKEN;
	return thisNode;
      } else {
	// Don't consume the token, try to match it as part of an expression
	return thisNode;
      }
    } else {
      if( must_match_paren ) {
	goatError((*curr)->line_no, "Could not find Right Paren to close function call parsing");
	astFreeNode(thisNode);
	return NULL;
      } else {
	// Leave the token, try to match it with the next node
	return thisNode;
      }
    }
  } else {
    goatError((*curr)->line_no, "Another function parameter expected after comma; none was matched.");
    astFreeNode( thisNode );
    return NULL;
  }
}

MATCHER_FOR( FunctionDef ) {
  Node *thisNode, *newChild;
  Token *savedcurr = *curr;
  int must_match = FALSE;

  if( TOKEN_IS_NOT_A( Lambda )) { return NULL; }
  CONSUME_TOKEN;

  if( TOKEN_IS_NOT_A( LeftParen )) {
    goatError((*curr)->line_no, "Unexpected %s found when a left parenthesis '(' was expected.", TOKEN_TYPES[(*curr)->type]);
    (*curr) = savedcurr;
    return NULL; 
  }
  CONSUME_TOKEN;
  
  thisNode = astCreateNode( FunctionDef );

  while((newChild = MATCH( ParameterDef ))) {
    astAppendChild(newChild, thisNode);
    
    // So if we match a right Parenthesis, that's a complete function call
    if( TOKEN_IS_A( RightParen )) {
      //CONSUME_TOKEN;
      break;
    }
    
    // If we match a comma, then we must match another parameter.
    if( TOKEN_IS_A( Comma ) && ! must_match) {
      must_match = TRUE;
      CONSUME_TOKEN;
      continue;
    }
    
    // If execution gets to here, we've encountered some other token
    goatError((*curr)->line_no, "FunctionDefinition: Unexpected %s found when a right parenthesis ')' was expected.", TOKEN_TYPES[(*curr)->type]);
    astFreeNode( thisNode );
    return NULL;
  }

  if( TOKEN_IS_NOT_A( RightParen)) {
    goatError((*curr)->line_no, "FunctionDefinition: Unexpected %s found when a right parenthesis ')' was expected.", TOKEN_TYPES[(*curr)->type]);
    astFreeNode(thisNode);
    return NULL;
  }
  CONSUME_TOKEN;

  if( TOKEN_IS_NOT_A( Newline )) {
    goatError((*curr)->line_no, "FunctionDefinition: Unexpected %s found when a Newline was expected.", TOKEN_TYPES[(*curr)->type]);
    astFreeNode(thisNode);
    (*curr) = savedcurr;
    return NULL;
  }
  CONSUME_TOKEN;
  
  if((int)(newChild = MATCH( Block ))) {
    astAppendChild(newChild, thisNode);
    return thisNode;  
  } else {
    goatError((*curr)->line_no, "No Block found for function definition");
    astFreeNode(thisNode);
    (*curr) = savedcurr;
    return NULL;
  }
}

MATCHER_FOR( ParameterDef ) {
  Node *thisNode;

  if(TOKEN_IS_A(Identifier)) {
    thisNode = astCreateNode( ParameterDef );
    thisNode->token = (*curr);
    CONSUME_TOKEN;
    return thisNode;
  } else {
    return NULL;
  }
}

MATCHER_FOR( Parameter ) {
  Node *thisNode, *newChild;

  //TODO: Add matching for named parameters
  if(( newChild = MATCH( Expression ))) {
    thisNode = astCreateNode( Parameter );
    astAppendChild( newChild, thisNode);
    return thisNode;
  }
  
  return NULL;
}

MATCHER_FOR( Conditional ) {
  Node *thisNode, *exprChild, *ifChild, *elseChild;
  Token *saved_curr = *curr;

  if( TOKEN_IS_NOT_A( If )) { return NULL; }
  thisNode = astCreateNode( Conditional );
  CONSUME_TOKEN;

  if(!(int)(exprChild = MATCH( Expression))) {
    astFreeNode(thisNode);
    (*curr) = saved_curr;
    goatError((*curr)->line_no, "Unexpected token %s found after if keyword.", TOKEN_TYPES[(*curr)->type]);
    return NULL;
  }
  astAppendChild(exprChild, thisNode);

  if( TOKEN_IS_NOT_A( Newline )) {
    astFreeNode(thisNode);
    (*curr) = saved_curr;
    goatError((*curr)->line_no, "Unexpected token %s found after if-expression; should be a new line.", TOKEN_TYPES[(*curr)->type]);
    return NULL;
  }
  CONSUME_TOKEN;

  // Match the block to be run if the condition executes to true
  if(!(int)(ifChild = MATCH( Block ))) {
    goatError((*curr)->line_no, "Unexpected token %s found after if keyword.", TOKEN_TYPES[(*curr)->type]);
    astFreeNode(thisNode);
    (*curr) = saved_curr;
    return NULL;
  }
  astAppendChild(ifChild, thisNode);

  if( TOKEN_IS_NOT_A( Else ) ) {
    // So no else clause
    return thisNode;
  }
  CONSUME_TOKEN;

  if( TOKEN_IS_NOT_A( Newline )) {
    astFreeNode(thisNode);
    (*curr) = saved_curr;
    goatError((*curr)->line_no, "Unexpected token %s found after else-expression; should be a new line.", TOKEN_TYPES[(*curr)->type]);
    return NULL;
  }
  CONSUME_TOKEN;

  if(!(int)(elseChild = MATCH( Block ))) {
    goatError((*curr)->line_no, "Unexpected token %s found after else keyword.", TOKEN_TYPES[(*curr)->type]);
    astFreeNode(thisNode);
    (*curr) = saved_curr;
    return NULL;
  }
  astAppendChild(elseChild, thisNode);
  return thisNode;
}

MATCHER_FOR( ClassDef ) {
  return NULL;
}


MATCHER_FOR( Assignment ) {
  Node *thisNode;
  if((thisNode = MATCH( ImmutableAssignment ))) {
    return thisNode;
  }

  if((thisNode = MATCH( MutableAssignment ))) {
    return thisNode;
  }

  return NULL;
}

MATCHER_FOR( MutableAssignment ) {
  Token *savedCurr = *curr, *variable;
  Node *newChild = NULL, *thisNode = NULL;
  
  if(TOKEN_IS_NOT_A( Identifier)) { return NULL; }
  variable = (*curr);
  CONSUME_TOKEN;
  
  if(TOKEN_IS_NOT_A( Equals )) {
    *curr = savedCurr; 
    return NULL;
  }
  CONSUME_TOKEN;
  
  if((newChild = MATCH( Expression ))) {
    thisNode = astCreateNode( MutableAssignment );
    thisNode->token = variable;
    astAppendChild(newChild, thisNode);
    return thisNode;
  }
  
  goatError((*curr)->line_no, "Unexpected token %s found after equals sign in a mutable assignment.", TOKEN_TYPES[(*curr)->type]);
  *curr = savedCurr; 
  return NULL;
}

MATCHER_FOR( ImmutableAssignment ) {
  Token *savedCurr = *curr, *variable;
  Node *newChild = NULL, *thisNode = NULL;
  
  if(TOKEN_IS_NOT_A( Identifier)) { return NULL; }
  variable = (*curr);
  CONSUME_TOKEN;
  
  if(TOKEN_IS_NOT_A( Colon )) {
    *curr = savedCurr; 
    return NULL;
  }
  CONSUME_TOKEN;
  
  if((newChild = MATCH( Expression ))) {
    thisNode = astCreateNode( ImmutableAssignment );
    thisNode->token = variable;
    astAppendChild(newChild, thisNode);
    return thisNode;
  }
  
  goatError((*curr)->line_no, "Unexpected token %s found after colon sign in a immutable assignment.", TOKEN_TYPES[(*curr)->type]);
  *curr = savedCurr; 
  return NULL;
}

MATCHER_FOR( ReturnStatement ) {
  Node *thisNode, *returnExpr;

  if( TOKEN_IS_NOT_A( Return )) {
    return NULL;
  }
  CONSUME_TOKEN;

  thisNode = astCreateNode( ReturnStatement );

  if(!(returnExpr = MATCH( Expression ))){
    returnExpr = astCreateNode( NullLiteral );
  }

  astAppendChild(returnExpr, thisNode);
  return thisNode;
}

MATCHER_FOR( ClassDefinition ) {
  Token *saved_curr = *curr;
  Node *thisNode, *newNode;

  if( TOKEN_IS_NOT_A( Class )) {
    return NULL;
  }
  CONSUME_TOKEN;

  if( TOKEN_IS_A( Identifier )) {
    thisNode = astCreateNode( ClassDefinition );
    thisNode->token = *curr;
  } else {
    goatError((*curr)->line_no, "Unexpected token %s found after class keyword. Identifier expected", TOKEN_TYPES[(*curr)->type]);
    (*curr) = saved_curr;
    return NULL;
  }
  CONSUME_TOKEN;
  
  if( TOKEN_IS_NOT_A( Newline )) {
    goatError((*curr)->line_no, "Unexpected token %s found after class name. Newline expected", TOKEN_TYPES[(*curr)->type]);
    (*curr) = saved_curr;
    return NULL;
  }
  CONSUME_TOKEN;


  if( TOKEN_IS_NOT_A( IndentIncrease )) {
    // Empty class
    return thisNode;
  }
  CONSUME_TOKEN;

  while((newNode = MATCH(Assignment))) {
    astAppendChild(newNode, thisNode);
    if( TOKEN_IS_A( Newline )) {
      CONSUME_TOKEN;
    } else {
      goatError((*curr)->line_no, "Unexpected token %s found in class definition block. Could not match assignment", TOKEN_TYPES[(*curr)->type]);
      return NULL;
    }
  }

  if( TOKEN_IS_A( IndentDecrease )) {
    CONSUME_TOKEN;
    return thisNode;
  } else {
    goatError((*curr)->line_no, "Unexpected token %s found when indent decrease to close class definition block expected.", TOKEN_TYPES[(*curr)->type]);
    astFreeNode(thisNode);
    (*curr) = saved_curr;
    return NULL;
  }
}
