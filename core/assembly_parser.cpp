#include <string>
#include <iostream>
#include "lexer.h"
#include "ast_node.h"
#include "parser.h"
#include "goat.h"

extern const char *TOKEN_TYPES[];

InlineAssemblyNode *Parser::MatchInlineAssembly() {
  TokenIterator savedPos = currentToken;
  InlineAssemblyNode *thisNode = NULL;
  InstructionNode *instruction = NULL;

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

  thisNode = new InlineAssemblyNode();

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

InstructionNode *Parser::MatchInstruction() {
  TokenIterator savedPos = currentToken;
  ASTLabelNode *label = NULL;
  OperandNode *operand = NULL;
  InstructionNode *thisNode = NULL;
  bool must_match = false;

  if( TokenIs(Label) ) {
    label = new ASTLabelNode( currentToken );
    ConsumeToken();
    
    // When a 
    if( TokenIs(Newline) ) {
      thisNode = new InstructionNode( currentToken );
      thisNode->AppendChild( label );
      ConsumeToken();
      return thisNode;
    }
  }

  if( TokenIs(Identifier) ) {
    thisNode = new InstructionNode( currentToken );
    ConsumeToken();

    if( label ) thisNode->AppendChild( label );

    while((operand = MATCH(Operand))) {
      thisNode->AppendOperand( operand );

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

OperandNode *Parser::MatchOperand() {
  OperandNode *thisNode = NULL;
  if((thisNode = MatchObjectOperand()) ||
     (thisNode = MatchHashOperand()) ||
     (thisNode = MatchAddressOperand()) ||
     (thisNode = MATCH(DirectOperand)) ||
     (thisNode = MATCH(IndirectOperand)) ||
     (thisNode = MatchImmediateOperand())) {
    return thisNode;
  }
  return NULL;
}

DirectOperandNode *Parser::MatchDirectOperand() {
  DirectOperandNode *thisNode = NULL;
  if( TokenIs(Identifier) ) {
    thisNode = new DirectOperandNode( currentToken );
    ConsumeToken();
  }
  return thisNode;
}

ImmediateOperandNode *Parser::MatchImmediateOperand() {
  ImmediateOperandNode *thisNode = NULL;
  if( TokenIs(Integer) ) {
    thisNode = new ImmediateOperandNode( currentToken );
    ConsumeToken();
  }
  return thisNode;
}

ObjectOperandNode *Parser::MatchObjectOperand() {
  ObjectOperandNode *thisNode = NULL;
  TokenIterator savedCurr = currentToken;

  if(TokenIs(Identifier)) {
    thisNode = new ObjectOperandNode(*currentToken);
    ConsumeToken();
  } else {
    return NULL;
  }

  if(TokenIs(Period)) {
    ConsumeToken();
  } else {
    ResetTokenPosition(savedCurr);
    delete thisNode;
    return NULL;
  }

  if(TokenIs(Identifier)) {
    thisNode->SetPropertyName(currentToken->Content());
    ConsumeToken();
    return thisNode;
  } else {
    ResetTokenPosition(savedCurr);
    delete thisNode;
    return NULL;
  }
}

HashOperandNode *Parser::MatchHashOperand() {
  HashOperandNode *thisNode = NULL;
  if(TokenIs(HashString)) {
    thisNode = new HashOperandNode( *currentToken );
    ConsumeToken();
  }
  return thisNode;
}

AddressOperandNode *Parser::MatchAddressOperand() {
  AddressOperandNode *thisNode = NULL;
  if(TokenIs(AddressString)) {
    thisNode = new AddressOperandNode( *currentToken );
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
    value = new IntegerLiteralNode( currentToken );
    ConsumeToken();
    thisNode->AppendChild( value );
    return thisNode;
  } else if ( TokenIs(Identifier) ) {
    value = new DirectOperandNode( currentToken );
    ConsumeToken();
    thisNode->AppendChild( value );
    return thisNode;
  } else {
    ResetTokenPosition( savedCurr );
    delete thisNode;
    return NULL;
  }
}
