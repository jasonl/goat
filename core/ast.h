/* 
 * File:   ast.h
 * Author: jason
 *
 * Created on 17 November 2009, 10:18 PM
 */

#ifndef _AST_H
#define	_AST_H

enum NODE_TYPE {
  Block,
  StatementGroup, Statement, ClassStatement,
  Expression,
  MutableAssignment, ImmutableAssignment,
  Conditional,
  ClassDefinition,
  FunctionDef, OneLineFunctionDef, BlockFunctionDef,
  ParameterDef,
  FunctionCall, Parameter, NamedParameter,
  IntegerLiteral, Variable, StringLiteral
};

static char *NODE_TYPES[] = { "Expression", "Parameter", "Named Parameter",
                             "Mutable Assignment", "Immutable Assignment"};

// AST node
typedef struct _Node {
    enum NODE_TYPE type;
    Token *token;
    struct _Node *parent;
    struct _Node *firstChild;
    struct _Node *nextSibling;
    struct _Node *prevSibling;
} Node;

// Macros
//------------------------------------------------------------------------------

#define MATCHER_FOR(name) Node *astMatch##name( Token **curr )
#define MATCHER_PROTOTYPE_FOR(name) Node *astMatch##name( Token** )
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
  return thisNode;

// Function Prototypes
//------------------------------------------------------------------------------
Node *astCreateNote( enum NODE_TYPE );
void astFreeNode( Node* );
void astAppendChild( Node*, Node* );

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

#endif	/* _AST_H */

