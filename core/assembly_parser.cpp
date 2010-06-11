#include <string>
#include "lexer.h"
#include "ast_node.h"
#include "parser.h"

MATCHER_FOR( IndirectOperand ) {
  TokenIterator savedCurr = currentToken;
  ASTIndirectOperandNode *thisNode = NULL;
  ASTIndirectOperandTermNode *termNode = NULL;

  if( TokenIsNot(LeftSquare) ) return NULL;
  ConsumeToken();

  if( TokenIsNot(Identifier) ) {
    // TODO: Raise syntax error
    ResetTokenPosition( savedCurr );
    return NULL;
  }

  thisNode = new ASTIndirectOperandNode( currentToken );
  ConsumeToken();

  while((termNode = MATCH(IndirectOperandTerm))) {
    thisNode->AppendChild( termNode );
  }
  
  if( TokenIsNot(RightSquare) ) {
    // TODO: Raise syntax error
    ResetTokenPosition( savedCurr );
    delete thisNode;
    return NULL;
  }

  ConsumeToken();
  return thisNode;
}

MATCHER_FOR( IndirectOperandTerm ) {
  TokenIterator savedCurr = currentToken;
  ASTIndirectOperandTermNode *thisNode = NULL;
  ASTNode *value = NULL;

  if( TokenIsNot( Plus ) &&
      TokenIsNot( Minus ) &&
      TokenIsNot( Multiply ) ) {
    return NULL;
  }

  thisNode = new ASTIndirectOperandTermNode( currentToken );
  ConsumeToken();

  if( TokenIs(Integer) ) {
    ConsumeToken();
    value = new ASTIntegerLiteralNode( currentToken );
    thisNode->AppendChild( value );
    return thisNode;
  } else if ( TokenIs(Identifier) ) {
    value = new ASTOperandNode( currentToken );
    ConsumeToken();
    thisNode->AppendChild( value );
    return thisNode;
  } else {
    ResetTokenPosition( savedCurr );
    delete thisNode;
    return NULL;
  }
}
