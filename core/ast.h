/* 
 * File:   ast.h
 * Author: jason
 *
 * Created on 17 November 2009, 10:18 PM
 */
#ifndef _AST_H
#define _AST_H

#include <string>
#include "ast_node.h"

const std::string NODE_TYPES[] = { 
  "SourceFile",
  "\x1b[1;33mBlock\x1b[0;37;00m",
  "StatementGroup", "Statement", "ClassStatement", "My",
  "\x1b[0;36mMutableAssignment\x1b[0;37;00m", "\x1b[0;36mImmutableAssignment\x1b[0;37;00m",
  "\x1b[1;35mConditional\x1b[0;37;00m",
  "ClassDefinition",
  "\x1b[1;31mFunctionDef\x1b[0;37;00m", "OneLineFunctionDef", "BlockFunctionDef",
  "ParameterDef",
  "\x1b[1;34mFunctionCall\x1b[0;37;00m", "Parameter", "NamedParameter",
  "IntegerLiteral", "Variable", "StringLiteral", "NullLiteral",
  "\x1b[1;32mReturnStatement\x1b[0;37;00m"
};

struct _Token;
struct _GoatState;

// Macros
//------------------------------------------------------------------------------

#define MATCHER_FOR(name) ASTNode *astMatch##name( struct _Token **curr )
#define MATCHER_PROTOTYPE_FOR(name) ASTNode *astMatch##name( struct _Token** )
#define MATCH(name) astMatch##name(curr)

#define TOKEN_IS_A( token_type ) ((*curr) && (*curr)->type == token_type)
#define TOKEN_IS_NOT_A( token_type ) (!(*curr) || (*curr)->type != token_type)

#define CONSUME_TOKEN *curr = (*curr)->next;

// Appends the subtree to a new node, and returns it; Note that it requires
// an available Node* named newNode in scope.
#define RETURN_SUBTREE( headNodeType, childSubTree ) \
  thisNode = astCreateNode( headNodeType ); \
  thisNode->firstChild = childSubTree; \
  childSubTree->parent = thisNode; \
  return thisNode;

// Creates a new terminal node (i.e. without any children) from the current
// token, and returns it
#define RETURN_TERMINAL_NODE( nodeType ) \
  thisNode = astCreateNode( nodeType); \
  thisNode->token = (*curr); \
  *curr = (*curr)->next; \
  return thisNode;

// Function Prototypes
//------------------------------------------------------------------------------

ASTNode *astCreateNode( ASTNode::NODE_TYPE );
void astFreeNode( ASTNode* );
void astAppendChild( ASTNode*, ASTNode* );
void astInsertFirstChild( ASTNode*, ASTNode* );
int astLookaheadFor( struct _Token **, enum TOKEN_TYPE );
int goatBuildAST( struct _GoatState* );


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
#endif
