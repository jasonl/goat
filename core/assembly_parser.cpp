#include <string>
#include <iostream>
#include "lexer.h"
#include "ast_node.h"
#include "parser.h"
#include "goat.hpp"

extern const char *TOKEN_TYPES[];

MATCHER_FOR( InlineAssembly ) {
  TokenIterator savedPos = currentToken;
  ASTInlineAssemblyNode *thisNode = NULL;
  ASTInstructionNode *instruction = NULL;

  if( TokenIsNot(Asm) ) {
    return NULL;
  }
  ConsumeToken();

  if( TokenIsNot(Newline) ) {
    ResetTokenPosition( savedPos );
    return NULL;
  }
  ConsumeToken();

  if( TokenIsNot(IndentIncrease) ) {
    goatError(CurrentSourcePosition(), "Expected indent increase after asm token, none found");
    ResetTokenPosition( savedPos );
    return NULL;
  }
  ConsumeToken();

  thisNode = new ASTInlineAssemblyNode();

  while((instruction = MATCH(Instruction)) || TokenIs(Newline)) {
    if( instruction ) {
      thisNode->AppendChild( instruction );
    } else {
      // It's a blank line...
      ConsumeToken();
    }
  }

  if( TokenIsNot(IndentDecrease) ) {
    goatError(CurrentSourcePosition(), "Expected indent decrease after asm block, found %s instead.", TOKEN_TYPES[currentToken->Type()]);
    ResetTokenPosition( savedPos );
    delete thisNode;
    return NULL;
  }
  ConsumeToken();

  return thisNode;
}

MATCHER_FOR( Instruction ) {
  TokenIterator savedPos = currentToken;
  ASTLabelNode *label = NULL;
  ASTNode *operand = NULL;
  ASTInstructionNode *thisNode = NULL;
  bool must_match = false;

  if( TokenIs(Label) ) {
    label = new ASTLabelNode( currentToken );
    ConsumeToken();
    
    // When a 
    if( TokenIs(Newline) ) {
      thisNode = new ASTInstructionNode( currentToken );
      thisNode->AppendChild( label );
      ConsumeToken();
      return thisNode;
    }
  }

  if( TokenIs(Identifier) ) {
    thisNode = new ASTInstructionNode( currentToken );
    ConsumeToken();

    if( label ) thisNode->AppendChild( label );

    while((operand = MATCH(Operand))) {
      thisNode->AppendChild( operand );

      if( TokenIs(Comma) ) {
	must_match = true;
	ConsumeToken();
	continue;
      }
      must_match = false;
    }

    if( !must_match && TokenIs(Newline) ) {
      ConsumeToken();
      return thisNode;
    }

    // We expected to find another operand but didn't
    goatError(CurrentSourcePosition(), "ASM Instruction: Expected to find another operand, but found %s instead.", TOKEN_TYPES[currentToken->Type()]);
    if( label ) delete label;
    ResetTokenPosition( savedPos );
    return NULL;
      
  } else {
    if( label ) delete label;
    ResetTokenPosition( savedPos );
    return NULL;
  }
}

INT_MATCHER_FOR( Operand ) {
  ASTNode *thisNode = NULL;
  if((thisNode = MATCH(DirectOperand)) ||
     (thisNode = MATCH(IndirectOperand)) ||
     (thisNode = MATCH(ImmediateOperand))) {
    return thisNode;
  }
  return NULL;
}

MATCHER_FOR( DirectOperand ) {
  ASTDirectOperandNode *thisNode = NULL;
  if( TokenIs(Identifier) ) {
    thisNode = new ASTDirectOperandNode( currentToken );
    ConsumeToken();
  }
  return thisNode;
}

MATCHER_FOR( ImmediateOperand ) {
  ASTImmediateOperandNode *thisNode = NULL;
  if( TokenIs(Integer) ) {
    thisNode = new ASTImmediateOperandNode( currentToken );
    ConsumeToken();
  }
  return thisNode;
}

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
    value = new ASTIntegerLiteralNode( currentToken );
    ConsumeToken();
    thisNode->AppendChild( value );
    return thisNode;
  } else if ( TokenIs(Identifier) ) {
    value = new ASTDirectOperandNode( currentToken );
    ConsumeToken();
    thisNode->AppendChild( value );
    return thisNode;
  } else {
    ResetTokenPosition( savedCurr );
    delete thisNode;
    return NULL;
  }
}
