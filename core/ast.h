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

#define MATCHER_FOR(name) ASTNode *Parser::Match##name()

// Appends the subtree to a new node, and returns it; Note that it requires
// an available Node* named newNode in scope.
#define RETURN_SUBTREE( headNodeType, childSubTree ) \
  thisNode = astCreateNode( headNodeType ); \
  thisNode->firstChild = childSubTree; \
  childSubTree->parent = thisNode; \
  return thisNode;

// Function Prototypes
//------------------------------------------------------------------------------

void astFreeNode( ASTNode* );
void astAppendChild( ASTNode*, ASTNode* );
void astInsertFirstChild( ASTNode*, ASTNode* );
int astLookaheadFor( struct _Token **, enum TOKEN_TYPE );
int goatBuildAST( struct _GoatState* );

#endif
