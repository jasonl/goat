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
  FunctionDefinition, OneLineFunctionDef, BlockFunctionDef,
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

// Appends the subtree to a new node, and returns it; Note that it requires
// an available Node* named newNode in scope.
#define RETURN_SUBTREE( headNodeType, childSubTree ) \
  newNode = astCreateNode( headNodeType ); \
  newNode->parent = childSubTree; \
  return newNode;

// Function Prototypes
//------------------------------------------------------------------------------
Node *astCreateNote( enum NODE_TYPE );
void astFreeNode( Node* );
MATCHER_PROTOTYPE_FOR( Expression );
MATCHER_PROTOTYPE_FOR( FunctionDefinition );
MATCHER_PROTOTYPE_FOR( FunctionCall );
MATCHER_PROTOTYPE_FOR( Parameter );
#endif	/* _AST_H */

