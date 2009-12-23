/*
 * ast.c
 *
 * A recursive-descent parser for the Goat language
 *
 * Grammar (EBNF)
 * -----------------------------------------------------------------------------
 * block                 = indent_increase, statement_group , indent_decrease;
 * statement_group       = statement, { statement };
 * statement             = [ assignment | function_call | conditional | class_def], newline;
 * class_statement       = assignment, newline;
 *
 * assignment            = mutable_assignment | immutable_assignment;
 * mutable_assignment    = identifier, equals, expression;
 * immutable_assignment  = identifier, colon, expression;
 *
 * conditional           = if, expression, block, [ else, block ];
 *
 * (* Class Definition *)
 * class_def             = class, identifier, indent_increase, { class_statement }, indent_decrease
 *
 * (* An expression is something which evaluates to an object: In the case of
 * a function, it evaluates to a function object *)
 * expression            = identifier | integer | string | function_call | function_definition;
 *
 * (* Function definitions *)
 * function_definition   = one_line_func_def | block_func_def;
 * one_line_func_def     = lambda, left_paren, { parameter_def, { comma, parameter_def}}, hash_rocket, statement, right_paren;
 * block_func_def        = lambda, left_paren, {parameter_def, {comma, parameter_def}}, right_paren, block;
 * parameter_def         = identifier, [ colon, expression ];
 *
 * (* Function calls *)
 * function_call         = [expression, [ period ] ], identifier, [ left_paren ], { parameter }, [right_paren];
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

#include "lexer.h"
#include "ast.h"
#include "goat.h"

const char *TOKEN_TYPES[]={"Whitespace", "Indent", "Comment", "NewLine", "Identifier",
			   "RightParen", "LeftParen", "Lambda", "Colon", "Period", "Comma",
			   "Equals", "End", "Integer", "String", "If", "Else", "HashRocket",
			   "IndentIncrease", "IndentDecrease"};

inline Node *astCreateNode( enum NODE_TYPE type ) {
  Node *newNode = malloc( sizeof(Node) );
  if (newNode == NULL) {
      goatFatalError("Unable to allocate sufficient memory during parsing.");
  }
  newNode->type = type; 
  return newNode;
}

// Recursively frees memory allocated to a node sub-tree
void astFreeNode( Node *node ) {
  Node *childNode = NULL, *tempNode = NULL;

  childNode = node->firstChild;

  while (childNode != NULL) {
    tempNode = childNode->nextSibling;
    astFreeNode( childNode );
    childNode = tempNode;
  }

  free(node);
}

MATCHER_FOR( Expression ) {
  Node *newNode = NULL;
  
  if( TOKEN_IS_A( String ) ) {
    newNode = astCreateNode( StringLiteral );
    newNode->token = *curr;
    *curr = (*curr)->next;
    return newNode;
  }

  if( TOKEN_IS_A( Integer )) {
    newNode = astCreateNode( IntegerLiteral );
    newNode->token = *curr;
    *curr = (*curr)->next;
    return newNode;
  }

  if( TOKEN_IS_A( Identifier )) {
    newNode = astCreateNode( Variable );
    newNode->token = *curr;
    *curr = (*curr)->next;
    return newNode;
  }

  if((newNode = MATCH( FunctionCall ))) {
    return newNode;
  }

  if((newNode = MATCH( FunctionDefinition ))) {
    return newNode;
  }
  
  return NULL;
}

MATCHER_FOR( FunctionCall) {
  Token *savedcurr = *curr;
  Node *thisNode = NULL, *newChild = NULL, *prevChild = NULL;
  int must_match = FALSE;

  // TODO: Add parsing logic for reciever object

  if( TOKEN_IS_NOT_A( Identifier )) { return NULL; }
  *curr = (*curr)->next;

  if( TOKEN_IS_NOT_A( LeftParen )) {
    *curr = savedcurr;
    return NULL;
  }
  
  *curr = (*curr)->next;
  thisNode = astCreateNode( FunctionCall );

  while((newChild = MATCH( Parameter ))) {
    if(prevChild == NULL) {
      // This is the first child node
      newChild->nextSibling = NULL;
      newChild->prevSibling = NULL;
      thisNode->firstChild = newChild;
      prevChild = newChild; // Keep a pointer for the next iteration
    }
    else {
      // There is already a child node
      newChild->nextSibling = NULL;
      newChild->prevSibling = prevChild;
      prevChild = newChild;
    }

    // So if we match a right Parenthesis, that's a complete function call
    if( TOKEN_IS_A( RightParen )) {
      *curr = (*curr)->next;
      return thisNode;
    }

    // If we match a comma, then we must match another parameter.
    if( TOKEN_IS_A( Comma )) {
      must_match = TRUE;
      *curr = (*curr)->next;
      continue;
    }

    // If execution gets to here, we've encountered some other token
    goatError((*curr)->line_no, "Unexpected %s found when a right parenthesis '(' was expected.", TOKEN_TYPES[(*curr)->type]);
    astFreeNode( thisNode );
    return NULL;
  }
  
  if( TOKEN_IS_A( RightParen ) && !must_match) {
    *curr = (*curr)->next;
    return thisNode;
  } else {
    goatError((*curr)->line_no, "Another function parameter expected after comma; none was matched.");
    astFreeNode( thisNode );
    return NULL;
  }
}

MATCHER_FOR( FunctionDefinition ) {
  return NULL;
}

MATCHER_FOR( Parameter ) {
  return NULL;
}

/*
// Matches a block - a group of statements with a common indent
MATCHER_FOR( Block ) {
  Node *newChild = NULL, *thisNode = NULL, *prevChild = NULL;
  Token *savedCurr = *curr;

  if(*curr->type != IndentIncrease) { return NULL }
  *curr = *curr->next;

  while(newChild = MATCH(Statement)) {
    if(thisNode == NULL) {
      thisNode = astCreateNode( Block );
    }
    
    newChild->parent = newNode;
    if(prevChild == NULL) {
      // This is the first child node
      newChild->nextSibling = NULL;
      newChild->prevSibling = NULL;
      thisNode->firstChild = newChild;
      prevChild = newChild; // Keep a pointer for the next iteration
    }
    else {
      // There is already a child node
      newChild->nextSibling = NULL;
      newChild->prevSibling = prevChild;
      prevChild = newChild
    }
  }

  if( *curr->type != IndentDecrease ) {
    goatError("Invalid token %s found in block.");
    astfreeNode( thisNode );
    return NULL;
  }
  return thisNode;
}


// Matches a parameter passed to a function call
MATCHER_FOR( Parameter ){
    Node *newChild, *newNode;

    if (newChild = MATCH( Expression )) {
        RETURN_SUBTREE(Parameter, newChild);
    } else if (newChild = MATCH(NamedParameter)) {
        RETURN_SUBTREE(NamedParameter, newChild);
    }
    return NULL;
}

// Matches a named parameter passed to a function call
MATCHER_FOR( NamedParameter ) {
    Token *savedCurr = *curr;
    Node *newChild = NULL, *newNode = NULL;

    if(*curr->type != Identifier) { return NULL; }
    *curr = *curr->next;

    if(*curr->type != Colon ) { *curr = savedCurr; return NULL; };
    *curr = *curr->next;

    if(newChild = MATCH( Expression )) {
        RETURN_SUBTREE(NamedParameter, newChild);
    }
    *curr = savedCurr; return NULL;
}

MATCHER_FOR( MutableAssignment ) {
    Token *savedCurr = *curr;
    Node *newChild = NULL, *newNode = NULL;
    
    if(*curr->type != Identifier) { return NULL; }
    *curr = *curr->next;
    
    if(*curr->type != Equals) { *curr = savedCurr; return NULL; }
    *curr = *curr->next;

    if(newChild = MATCH( Expression )) {
        RETURN_SUBTREE(MutableAssignment, newChild);
    }
    *curr = savedCurr; return NULL;
}

MATCHER_FOR( ImmutableAssignment ) {
    Token *savedCurr = *curr;
    Node *newChild = NULL, *newNode = NULL;
    
    if(*curr->type != Identifier) { return NULL; }
    *curr = *curr->next;
    
    if(*curr->type != Colon) { *curr = savedCurr; return NULL; }
    *curr = *curr->next;

    if(newChild = MATCH( Expression )) {
        RETURN_SUBTREE(ImmutableAssignment, newChild);
    }
    else {
        goatError("Unexpected %s found; expecting an Expression to be evaluated", *NODE_TYPES[*curr->type])
        *curr = savedCurr; return NULL;
    }
}

MATCHER_FOR( FunctionCall ) {
    Token *savedCurr = *curr;
    Node *newChild = NULL, *newNode = NULL;

    if(newChild = MATCH( Expression )) {
        *curr = *curr->next;

        if(*curr->type == Period) { *curr = *curr->next; }

        if(*curr->type == Identifier) {
            *curr = *curr->next;
        }
        else {
            goatError("Unexpected %s found; expecting an Identifier denoting a function to call", *NODE_TYPES[*curr->type]);
            *curr = savedCurr; return NULL;
        }
    }
    else if (*curr->type == Identifier) {
        // Add implied AST nodes for the "my" object
    }
    else { *curr = savedCurr; return NULL; }
}

MATCHER_FOR( FunctionDefinition ) {
  Token *savedCurr = *curr;
  Node *newChild = NULL, *newNode = NULL;

  if(newChild = MATCH( OneLineFunctionDef )) {
    // Return the actual function definition node itself, this rule is for convenience only
    return newChild;
  }
  else if(newChild = MATCH( BlockFunctionDef )) {
    return newChild;
  }
  return NULL;
} */
