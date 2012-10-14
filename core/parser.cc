/*
 * ast.c
 *
 * A recursive-descent parser for the Goat language
 *
 * Grammar (EBNF)
 * -----------------------------------------------------------------------------
 * block                 = indent_increase,{ statement_group }, indent_decrease;
 * statement_group       = statement, { statement }
 * statement             = [ assignment | function_call | conditional | class_def | singleton_def | return_statement | inline_assembly | include_statement ], newline;
 *
 *
 * inline_assembly_block = asm, indent_increase, assembly_statement, {assembly_statement}, indent_decrease
 * assembly_statement    = [ label ], identifier, { assembly_operand, { comma, assembly_operand }}
 * assembly_operand      = identifier | indirect_operand | integer
 * indirect_operand      = left_square, identifier, [indirect_operand_term], [indirect_operand_term], right_square
 * indirect_operand_term = plus | minus | multiply, identifier | integer
 *
 * include_statement     = include, string_literal;
 *
 * assignment            = assignment_target, equals, expression;
 * assignment_target     = identifier | class_variable
 * constant_assignment   = identifier, colon, expression;
 *
 * method_assignment     = identifier, colon, expression
 * class_method_assignment = self, period, identifier, colon, expression
 *
 * conditional           = if, expression, newline, block, [ else, newline, block ];
 *
 * return_statement      = return, [expression];
 *
 * (* Class Definition *)
 * class_def             = class, identifier, indent_increase, { method_assignment | class_method_assignment }, indent_decrease
 * singleton_def         = singleton, identifier, indent_increase, { method_assignment }, indent_decrease
 *
 * (* An expression is something which evaluates to an object: In the case of
 * a function, it evaluates to a function object *)
 * expression            = identifier | class_variable | integer | string | function_definition | function_call | self;
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
 * class_variable        = "@", { non_terminating_character };
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
#include "goat.h"
#include "source_file.h"
#include "ast_node.h"
#include "parser.h"

const char *TOKEN_TYPES[]={
	"Asm",
	"Class",
	"ClassVar",
	"Colon",
	"Comma",
	"Comment",
	"Else",
	"End",
	"EndOfFile",
	"Equals",
	"False",
	"Identifier",
	"If",
	"Include",
	"Indent",
	"IndentDecrease",
	"IndentIncrease",
	"Integer",
	"Lambda",
	"LeftParen",
	"New",
	"Newline",
	"Null",
	"Period",
	"Return",
	"RightParen",
	"Self",
	"Singleton",
	"String",
	"True",
	"UnsignedInteger",
	"Whitespace",

	// Assembly-only tokens
	"AddressString",
	"HashString",
	"Label",
	"LeftSquare",
	"Minus",
	"Multiply",
	"Plus",
	"RightSquare"
};

Parser::Parser(::SourceFile* _sourceFile) : sourceFile(_sourceFile)
{
	currentToken = sourceFile->FirstToken();
	endToken = sourceFile->LastToken();
}

ASTNode * Parser::Parse( ASTNode *astRoot ) {
  ASTNode *newChild;

  // Remove any leading newlines - e.g. from comments
  // The lexer includes a newline token after a comment
  while( TokenIs( Newline )) {
    ConsumeToken();
  }


  while((newChild = MATCH(Statement)) || TokenIs(Newline)) {
    if(newChild) {
      astRoot->AppendChild(newChild);
    } else if ( TokenIs(Newline) ) {
      ConsumeToken();
    } else if( TokenIs( EndOfFile)) {
      return astRoot;
    } else {
      // Found something on a line we couldn't match
      goatError(CurrentSourcePosition(), "Unexpected token %s[%s] found.", TOKEN_TYPES[currentToken->Type()], currentToken->Content().c_str() );
      delete astRoot;
      return NULL;
    }
  }

  return astRoot;
}

// Helper function to perform look-aheads in the token stream
// where we need to resolve ambiguities.
bool Parser::LookAheadFor( TokenType token_type) {
  TokenIterator nextToken = currentToken;
  nextToken++;
  if(nextToken == endToken) return FALSE;

  return nextToken->Type() == token_type;
}

bool Parser::TokenIs( TokenType type ) {
  return ( currentToken != endToken &&
	   currentToken->Type() == type );
}

bool Parser::TokenIsNot( TokenType type ) {
  return ( currentToken == endToken ||
	   currentToken->Type() != type );
}

// Matches a block - a group of statements with a common indent
BlockNode *Parser::MatchBlock() {
  BlockNode *thisNode = NULL;
  ASTNode *newChild = NULL;

  if(TokenIsNot( IndentIncrease )) { return NULL; }
  ConsumeToken();

  thisNode = new BlockNode();

  // Match at least one statement
  if((newChild = MATCH(Statement)) || TokenIs(Newline)) {
    if(newChild) {
      thisNode->AppendChild(newChild);
    } else {
      ConsumeToken();
    }
  } else {
    goatError(CurrentSourcePosition(), "Could not match a statement in block");
    delete thisNode;
    return NULL;
  }

  while((newChild = MATCH(Statement)) || TokenIs(Newline) ) {
    if( newChild ) {
      thisNode->AppendChild( newChild );
    } else {
      ConsumeToken();
    }
  }

  if( TokenIsNot( IndentDecrease )) {
    goatError(CurrentSourcePosition(), "Invalid token %s found in block.", TOKEN_TYPES[currentToken->Type()]);
    delete thisNode;
    return NULL;
  }

  ConsumeToken();
  return thisNode;
}

ASTNode* Parser::MatchStatement()
{
  ASTNode *thisNode;

  if((thisNode = MatchAssignment()) ||
     (thisNode = MATCH( FunctionCall )) ||
     (thisNode = MATCH( Conditional )) ||
     (thisNode = MATCH( InlineAssembly )) ||
     (thisNode = MATCH( ClassDefinition )) ||
	 (thisNode = MatchSingletonDefinition()) ||
	 (thisNode = MatchIncludeStatement()) ||
     (thisNode = MatchReturnStatement())) {
    return thisNode;
  }

  return NULL;
}

ASTNode *Parser::MatchIncludeStatement() {
	TokenIterator savedCurr = currentToken;

	if(TokenIsNot(Include)) {
		return NULL;
	}

	ConsumeToken();

	if(TokenIsNot(String)) {
		ResetTokenPosition(savedCurr);
		goatError(CurrentSourcePosition(), "A string literal must be found after an include statement.");
		return NULL;
	}

	ASTNode *dummyNode = new SourceFileNode;
	::SourceFile includedFile( sourceFile->ResolveIncludedFile(currentToken->Content()), true);

	includedFile.SetBuildSet(sourceFile->GetBuildSet());
	includedFile.Tokenize();
	includedFile.ParseOntoNode(dummyNode);
	includedFile.RetainAST();

	ConsumeToken();

	return dummyNode->FirstChild();
}

// Match an expression
INT_MATCHER_FOR( Expression ) {
  TokenIterator savedCurr = currentToken;
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
	goatError(CurrentSourcePosition(), "Expression: expected to find a right parenthesis, found a %s instead.", TOKEN_TYPES[currentToken->Type()]);
	ResetTokenPosition( savedCurr );
	return NULL;
      }
    }
  }

  if((thisNode = MATCH( FunctionDef ))) {
    return thisNode;
  }

  if( TokenIs( String ) ) {
	thisNode = new StringLiteralNode( currentToken->Content() );
    ConsumeToken();
    return thisNode;
  }

  if( TokenIs( Integer )) {
	thisNode = new IntegerLiteralNode( currentToken->Content() );
    ConsumeToken();
    return thisNode;
  }

  if (TokenIs(UnsignedInteger)) {
	  thisNode = new UnsignedIntegerLiteralNode(currentToken->Content());
	  ConsumeToken();
	  return thisNode;
  }

  if( TokenIs( Identifier )) {
	  thisNode = new VariableNode( currentToken->Content() );
    ConsumeToken();
    return thisNode;
  }

  if(TokenIs(ClassVar)) {
	  thisNode = new ClassVariableNode(currentToken->Content());
	  ConsumeToken();
	  return thisNode;
  }

  if(TokenIs(True)) {
	  thisNode = new TrueLiteralNode();
	  ConsumeToken();
	  return thisNode;
  }

  if(TokenIs(False)) {
	  thisNode = new FalseLiteralNode();
	  ConsumeToken();
	  return thisNode;
  }

  if (TokenIs(Null)) {
	  thisNode = new NullLiteralNode;
	  ConsumeToken();
	  return thisNode;
  }

  if(TokenIs(Self)) {
	  thisNode = new SelfNode();
	  ConsumeToken();
	  return thisNode;
  }

  return NULL;
}

// Matches an object which a function call can be made to
INT_MATCHER_FOR( Receiver ) {
  TokenIterator savedCurr = currentToken;
  ASTNode *thisNode = NULL;

  if (TokenIs( LeftParen )) {
    ConsumeToken();
    if ((thisNode = MATCH(Expression))) {
      if (TokenIs( RightParen)) {
	ConsumeToken();
	return thisNode;
      }
      else {
	goatError(CurrentSourcePosition(), "Receiver: expected to find a right parenthesis, found a %s instead.", TOKEN_TYPES[currentToken->Type()]);
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
	  thisNode = new VariableNode( currentToken->Content() );
      ConsumeToken();
      return thisNode;
      }
  }

  if (TokenIs(ClassVar)) {
	  thisNode = new ClassVariableNode(currentToken->Content());
	  ConsumeToken();
	  return thisNode;
  }


  if (TokenIs( String ) ) {
	thisNode = new StringLiteralNode( currentToken->Content() );
    ConsumeToken();
    return thisNode;
  }

  if (TokenIs( Integer )) {
	thisNode = new IntegerLiteralNode( currentToken->Content() );
    ConsumeToken();
    return thisNode;
  }

  if (TokenIs(UnsignedInteger)) {
	  thisNode = new UnsignedIntegerLiteralNode(currentToken->Content());
	  ConsumeToken();
	  return thisNode;
  }

  if (TokenIs(Null)) {
	  thisNode = new NullLiteralNode;
	  ConsumeToken();
	  return thisNode;
  }

  return NULL;
}

FunctionCallNode *Parser::MatchFunctionCall() {
  FunctionCallNode *thisNode = NULL;
  FunctionCallNode *newParent = NULL;
  ASTNode *receiver = NULL;
  TokenIterator savedCurr = currentToken;

  receiver = MATCH( Receiver );

  if(!(thisNode = MATCH( MethodInvocation ))) {
    ResetTokenPosition( savedCurr );
    if(receiver) delete receiver;
    return NULL;
  }

  while((newParent = MATCH( MethodInvocation ))) {
    newParent->InsertFirstChild( thisNode );
    thisNode = newParent;
  }

  if( receiver ) {
    thisNode->AddReceiver( receiver );
  } else {
	  thisNode->AddReceiver(new SelfNode);
  }

  return thisNode;
}

// This is different from the usual, because we break this out
// to resolve an potential recursion in the grammar.

FunctionCallNode *Parser::MatchMethodInvocation() {
  TokenIterator functionName, savedCurr = currentToken;
  FunctionCallNode *thisNode = NULL;
  ASTNode *newChild = NULL;
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

  thisNode = new FunctionCallNode( functionName->Content() );

  while((newChild = MATCH( Parameter ))) {
    thisNode->AppendChild(newChild);

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
    goatError(CurrentSourcePosition(), "MethodInvocation: Unexpected %s found when a right parenthesis ')' was expected.", TOKEN_TYPES[currentToken->Type()]);
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

FunctionDefNode *Parser::MatchFunctionDef() {
  FunctionDefNode *thisNode;
  ParameterDefNode *parameter;
  ASTNode *functionBody;
  TokenIterator savedCurr = currentToken;
  bool must_match = false;


  if( TokenIsNot( Lambda )) { return NULL; }
  ConsumeToken();

  if( TokenIsNot( LeftParen )) {
    goatError(CurrentSourcePosition(), "Unexpected %s found when a left parenthesis '(' was expected.", TOKEN_TYPES[currentToken->Type()]);
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  ConsumeToken();

  thisNode = new FunctionDefNode;

  while((parameter = MatchParameterDef())) {
    thisNode->AddParameterDef( parameter );

    // So if we match a right Parenthesis, that's a complete function call
    if( TokenIs( RightParen )) {
	  must_match = false;
      break;
    }

    // If we match a comma, then we must match another parameter.
    if( TokenIs( Comma )) {
      must_match = true;
      ConsumeToken();
      continue;
    }

    // If execution gets to here, we've encountered some other token
    goatError(CurrentSourcePosition(), "FunctionDefinition: Unexpected %s found when a right parenthesis ')' was expected.", TOKEN_TYPES[currentToken->Type()]);
    delete thisNode;
    return NULL;
  }

  if(must_match)
  {
	  goatError(CurrentSourcePosition(), "FunctionDefinition: Expected to find another parameter after comma.");
	  delete thisNode;
	  return NULL;
  }

  if(TokenIsNot(RightParen)) {
    goatError(CurrentSourcePosition(), "FunctionDefinition: Unexpected %s found when a right parenthesis ')' was expected.", TOKEN_TYPES[currentToken->Type()]);
    delete thisNode;
    return NULL;
  }
  ConsumeToken();

  if (TokenIsNot( Newline )) {
    goatError(CurrentSourcePosition(), "FunctionDefinition: Unexpected %s found when a Newline was expected.", TOKEN_TYPES[currentToken->Type()]);
    delete thisNode;
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  ConsumeToken();

  if ((functionBody = MatchBlock())) {
    thisNode->AddBody(functionBody);
    return thisNode;
  } else {
    goatError(CurrentSourcePosition(), "No Block found for function definition");
    delete thisNode;
    ResetTokenPosition( savedCurr );
    return NULL;
  }
}

ParameterDefNode *Parser::MatchParameterDef() {
  ParameterDefNode *thisNode;

  if (TokenIs( Identifier )) {
	  thisNode = new ParameterDefNode( currentToken->Content() );
    ConsumeToken();
    return thisNode;
  } else {
    return NULL;
  }
}

ParameterNode *Parser::MatchParameter() {
  ParameterNode *thisNode;
  ASTNode *newChild;

  //TODO: Add matching for named parameters
  if(( newChild = MATCH( Expression ))) {
    thisNode = new ParameterNode;
    thisNode->AppendChild(newChild);
    return thisNode;
  }

  return NULL;
}

ConditionalNode *Parser::MatchConditional() {
  ConditionalNode *thisNode;
  ASTNode *exprChild;
  BlockNode *ifChild, *elseChild;
  TokenIterator savedCurr = currentToken;

  if (TokenIsNot( If )) { return NULL; }
  thisNode = new ConditionalNode;
  ConsumeToken();

  if (!(exprChild = MATCH( Expression))) {
    delete thisNode;
    ResetTokenPosition( savedCurr );
    goatError(CurrentSourcePosition(), "Unexpected token %s found after if keyword.", TOKEN_TYPES[currentToken->Type()]);
    return NULL;
  }
  thisNode->AddExpression(exprChild);

  if (TokenIsNot( Newline )) {
    delete thisNode;
    ResetTokenPosition( savedCurr );
    goatError(CurrentSourcePosition(), "Unexpected token %s found after if-expression; should be a new line.", TOKEN_TYPES[currentToken->Type()]);
    return NULL;
  }
  ConsumeToken();

  // Match the block to be run if the condition executes to true
  if(!(ifChild = MatchBlock())) {
    goatError(CurrentSourcePosition(), "Unexpected token %s found after if keyword.", TOKEN_TYPES[currentToken->Type()]);
    delete thisNode;
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  thisNode->AddIfBlock(ifChild);

  if (TokenIsNot( Else ) ) {
    // So no else clause
    return thisNode;
  }
  ConsumeToken();

  if (TokenIsNot( Newline )) {
    delete thisNode;
    ResetTokenPosition( savedCurr );
    goatError(CurrentSourcePosition(), "Unexpected token %s found after else-expression; should be a new line.", TOKEN_TYPES[currentToken->Type()]);
    return NULL;
  }
  ConsumeToken();

  if (!(elseChild = MatchBlock())) {
    goatError(CurrentSourcePosition(), "Unexpected token %s found after else keyword.", TOKEN_TYPES[currentToken->Type()]);
    delete thisNode;
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  thisNode->AddElseBlock(elseChild);
  return thisNode;
}


ASTNode *Parser::MatchAssignment() {
  ASTNode *thisNode = NULL;
  if( (thisNode = MatchConstantAssignment()) ) return thisNode;
  if( (thisNode = MatchMutableAssignment()) ) return thisNode;
  return NULL;
}

AssignmentTargetNode* Parser::MatchAssignmentTarget()
{
	if(TokenIs(Identifier))
	{
		return new VariableNode(currentToken->Content());
	}

	if(TokenIs(ClassVar))
	{
		return new ClassVariableNode(currentToken->Content());
	}

	return NULL;
}

MutableAssignmentNode *Parser::MatchMutableAssignment()
{
	TokenIterator variable, savedCurr = currentToken;
	AssignmentTargetNode *target = MatchAssignmentTarget();;
	ASTNode *rValue;

	if(target == NULL)
		return NULL;

	ConsumeToken();

	if(TokenIsNot( Equals ))
	{
		ResetTokenPosition( savedCurr );
		return NULL;
	}

	ConsumeToken();

	if((rValue = MatchExpression()))
	{
		return new MutableAssignmentNode(target, rValue);
	}

	goatError(CurrentSourcePosition(), "Unexpected token %s found after equals sign in a mutable assignment.", TOKEN_TYPES[currentToken->Type()]);
	ResetTokenPosition( savedCurr );
	return NULL;
}

ConstantAssignmentNode *Parser::MatchConstantAssignment() {
  TokenIterator variable, savedCurr = currentToken;
  ConstantAssignmentNode *thisNode = NULL;
  ASTNode *rValue;

  if(TokenIsNot( Identifier )) { return NULL; }
  variable = currentToken;
  ConsumeToken();

  if(TokenIsNot( Colon )) {
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  ConsumeToken();

  if((rValue = MATCH( Expression ))) {
	thisNode = new ConstantAssignmentNode( variable->Content() );
    thisNode->SetRValue( rValue );
    return thisNode;
  }

  goatError(CurrentSourcePosition(), "Unexpected token %s found after colon sign in a immutable assignment.", TOKEN_TYPES[currentToken->Type()]);
  ResetTokenPosition( savedCurr );
  return NULL;
}





ReturnStatementNode *Parser::MatchReturnStatement() {
  ReturnStatementNode *thisNode;
  ASTNode *returnExpr;

  if( TokenIsNot( Return )) {
    return NULL;
  }
  ConsumeToken();

  thisNode = new ReturnStatementNode;

  if(!(returnExpr = MATCH( Expression ))){
    returnExpr = new NullLiteralNode;
  }

  // TODO: This is too permissive - it should only return a null literal when
  // the return statement is followed by a newline.

  thisNode->SetReturnValue( returnExpr );
  return thisNode;
}

ClassDefinitionNode *Parser::MatchClassDefinition() {
  ClassDefinitionNode *thisNode;
  ASTNode *newNode;
  TokenIterator savedCurr = currentToken;
  std::string className;

  if( TokenIsNot( Class )) {
    return NULL;
  }
  ConsumeToken();

  if( TokenIs( Identifier )) {
	  className = currentToken->Content();
	  thisNode = new ClassDefinitionNode( currentToken->Content() );
  } else {
    goatError(CurrentSourcePosition(), "Unexpected token %s found after class keyword. Identifier expected", TOKEN_TYPES[currentToken->Type()]);
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  ConsumeToken();

  if( TokenIsNot( Newline )) {
    goatError(CurrentSourcePosition(), "Unexpected token %s found after class name. Newline expected", TOKEN_TYPES[currentToken->Type()]);
    ResetTokenPosition( savedCurr );
    return NULL;
  }
  ConsumeToken();

  if( TokenIsNot( IndentIncrease )) {
    // Empty class
    return thisNode;
  }
  ConsumeToken();

  MethodAssignmentNode *newMethod = NULL;
  ClassMethodAssignmentNode *newClassMethod = NULL;

  while((newMethod = MatchMethodAssignment()) ||
		(newClassMethod = MatchClassMethodAssignment()) ||
		TokenIs(Newline)) {
	  if (newMethod)
	  {
		  thisNode->AppendMethod(newMethod);
	  }
	  else if (newClassMethod)
	  {
		  thisNode->AppendClassMethod(newClassMethod);
	  }
 	  else if (TokenIs(Newline))
	  {
		  ConsumeToken();
	  }
	  else
	  {
		  goatError(CurrentSourcePosition(), "Unexpected token %s found in class definition block. Could not match assignment", TOKEN_TYPES[currentToken->Type()]);
		  ResetTokenPosition( savedCurr );
		  return NULL;
	  }
  }

  if( TokenIs( IndentDecrease )) {
    ConsumeToken();
	sourceFile->RegisterClass(className);
    return thisNode;
  } else {
    goatError(CurrentSourcePosition(), "Unexpected token %s found when indent decrease to close class definition block expected.", TOKEN_TYPES[currentToken->Type()]);
    delete thisNode;
    ResetTokenPosition( savedCurr );
    return NULL;
  }
}

SingletonDefinitionNode *Parser::MatchSingletonDefinition()
{
	SingletonDefinitionNode *thisNode;
	ASTNode *newNode;
	TokenIterator savedCurr = currentToken;
	std::string singletonName;

	if (TokenIsNot(Singleton))
		return NULL;

	ConsumeToken();

	if (TokenIs(Identifier)) {
		singletonName = currentToken->Content();
		thisNode = new SingletonDefinitionNode(currentToken->Content());
	} else {
		goatError(CurrentSourcePosition(), "Unexpected token %s found after singleton keyword. Identifier expected", TOKEN_TYPES[currentToken->Type()]);
		ResetTokenPosition(savedCurr);
		return NULL;
	}

	ConsumeToken();

	if ( TokenIsNot( Newline )) {
		goatError(CurrentSourcePosition(), "Unexpected token %s found after class name. Newline expected", TOKEN_TYPES[currentToken->Type()]);
		ResetTokenPosition(savedCurr);
		return NULL;
	}

	ConsumeToken();

	if (TokenIsNot(IndentIncrease))
		return thisNode;

	ConsumeToken();

	while ((newNode = MatchMethodAssignment()) || TokenIs(Newline)) {
		if (newNode) {
			thisNode->AppendChild(newNode);
		} else if (TokenIs(Newline)) {
			ConsumeToken();
		} else {
			goatError(CurrentSourcePosition(), "Unexpected token %s found in singleton definition block. Could not match assignment", TOKEN_TYPES[currentToken->Type()]);
			ResetTokenPosition( savedCurr );
			return NULL;
		}
	}

	if (TokenIs(IndentDecrease)) {
		ConsumeToken();
		sourceFile->RegisterSingleton(singletonName);
		return thisNode;
	} else {
		goatError(CurrentSourcePosition(), "Unexpected token %s found when indent decrease to close singleton definition block expected.", TOKEN_TYPES[currentToken->Type()]);
		delete thisNode;
		ResetTokenPosition(savedCurr);
		return NULL;
	}
}

MethodAssignmentNode *Parser::MatchMethodAssignment()
{
	TokenIterator variable, savedCurr = currentToken;
	MethodAssignmentNode *thisNode = NULL;
	FunctionDefNode *rValue;

	if(TokenIsNot(Identifier))
		return NULL;

	variable = currentToken;
	ConsumeToken();

	if(TokenIsNot(Colon))
	{
		ResetTokenPosition(savedCurr);
		return NULL;
	}
	ConsumeToken();

	if((rValue = MatchFunctionDef()))
	{
		thisNode = new MethodAssignmentNode(variable->Content());
		thisNode->SetRValue(rValue);
		return thisNode;
	}

	goatError(CurrentSourcePosition(), "Unexpected token %s found after colon sign in method assignment", TOKEN_TYPES[currentToken->Type()]);
	ResetTokenPosition(savedCurr);
	return NULL;
}

ClassMethodAssignmentNode *Parser::MatchClassMethodAssignment()
{
	TokenIterator variable, savedCurr = currentToken;
	ClassMethodAssignmentNode *thisNode = NULL;
	FunctionDefNode *rValue;

	if(TokenIsNot(Self))
		return NULL;

	ConsumeToken();

	if(TokenIsNot(Period))
	{
		ResetTokenPosition(savedCurr);
		return NULL;
	}
	ConsumeToken();

	if(TokenIsNot(Identifier))
		return NULL;

	variable = currentToken;
	ConsumeToken();

	if(TokenIsNot(Colon))
	{
		ResetTokenPosition(savedCurr);
		return NULL;
	}
	ConsumeToken();

	if((rValue = MatchFunctionDef()))
	{
		thisNode = new ClassMethodAssignmentNode(variable->Content());
		thisNode->SetRValue(rValue);
		return thisNode;
	}

	goatError(CurrentSourcePosition(), "Unexpected token %s found after colon sign in method assignment", TOKEN_TYPES[currentToken->Type()]);
	ResetTokenPosition(savedCurr);
	return NULL;
}
