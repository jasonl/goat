#include "goat.h"
#include "lexer.h"
#include "ast_node.h"
#include "parser.h"

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
  std::string label;
  OperandNode *operand = NULL;
  InstructionNode *thisNode = NULL;
  bool must_match = false;

  if( TokenIs(Label) ) {
	label = currentToken->Content();
    ConsumeToken();

    // When a
    if( TokenIs(Newline) ) {
	  thisNode = new InstructionNode(label, currentToken->Content());
      ConsumeToken();
      return thisNode;
    }
  }

  if( TokenIs(Identifier) ) {
	  thisNode = new InstructionNode(label, currentToken->Content());
	  ConsumeToken();

	  while((operand = MATCH(Operand))) {
		  thisNode->AppendOperand( operand );

		  if( TokenIs(Comma) ) {
			  must_match = true;
			  ConsumeToken();
			  continue;
		  }

		  if(TokenIs(Newline))
		  {
			  must_match = false;
			  break;
		  }

		  goatError(CurrentSourcePosition(), "ASM Instruction: Unexpected token found: %s", TOKEN_TYPES[currentToken->Type()]);
		  ResetTokenPosition( savedPos );
		  return NULL;
	  }

	  if(must_match) {
		  goatError(CurrentSourcePosition(), "ASM Instruction: Expected to find another operand after a comma");
		  ResetTokenPosition( savedPos );
		  return NULL;
	  }

	  if(TokenIs(Newline)) {
		  ConsumeToken();
		  return thisNode;
	  }

    // We expected to find another operand but didn't
    goatError(CurrentSourcePosition(), "ASM Instruction: Expected to find another operand, but found %s instead.", TOKEN_TYPES[currentToken->Type()]);
    ResetTokenPosition( savedPos );
    return NULL;

  } else {
    ResetTokenPosition( savedPos );
    return NULL;
  }
}

OperandNode *Parser::MatchOperand() {
  OperandNode *thisNode = NULL;
  if((thisNode = MatchModifiedOperand()) ||
	 (thisNode = MatchObjectOperand()) ||
     (thisNode = MatchHashOperand()) ||
     (thisNode = MatchAddressOperand()) ||
     (thisNode = MATCH(DirectOperand)) ||
     (thisNode = MatchIndirectOperand()) ||
	 (thisNode = MatchExternLabel()) ||
     (thisNode = MatchImmediateOperand())) {
    return thisNode;
  }
  return NULL;
}

OperandNode *Parser::MatchModifiedOperand()
{
	TokenIterator savedPos = currentToken;
	OperandNode *thisNode = NULL;
	std::string modifier;

	if(TokenIsNot(Identifier)) return NULL;
	modifier = currentToken->Content();
	ConsumeToken();

	if((thisNode = MatchObjectOperand()) ||
	   (thisNode = MatchHashOperand()) ||
	   (thisNode = MatchAddressOperand()) ||
	   (thisNode = MATCH(DirectOperand)) ||
	   (thisNode = MatchIndirectOperand()) ||
	   (thisNode = MatchExternLabel()) ||
	   (thisNode = MatchImmediateOperand())) {

		if(modifier == "dword") {
			thisNode->SetSize(Operand::Dword);
		} else if (modifier == "word") {
			thisNode->SetSize(Operand::Word);
		} else if (modifier == "byte") {
			thisNode->SetSize(Operand::Byte);
		} else {
			goatError(CurrentSourcePosition(), "Unexpected operand modifier %s found.", modifier.c_str());
			delete thisNode;
			ResetTokenPosition(savedPos);
			return NULL;
		}

		return thisNode;
	}

	ResetTokenPosition(savedPos);
	return NULL;
}

DirectOperandNode *Parser::MatchDirectOperand() {
  DirectOperandNode *thisNode = NULL;
  if( TokenIs(Identifier) ) {
	thisNode = new DirectOperandNode(currentToken->Content());
    ConsumeToken();
  }
  return thisNode;
}

ExternLabelNode *Parser::MatchExternLabel()
{
	ExternLabelNode *thisNode = NULL;
	if(TokenIs(String))
	{
		thisNode = new ExternLabelNode(currentToken->Content());
		ConsumeToken();
	}
	return thisNode;
}

ImmediateOperandNode *Parser::MatchImmediateOperand() {
  ImmediateOperandNode *thisNode = NULL;
  if( TokenIs(Integer) ) {
	thisNode = new ImmediateOperandNode(currentToken->Content());
    ConsumeToken();
  }
  return thisNode;
}

ObjectOperandNode *Parser::MatchObjectOperand() {
  ObjectOperandNode *thisNode = NULL;
  TokenIterator savedCurr = currentToken;
  std::string variable;

  if(TokenIs(Identifier)) {
	variable = currentToken->Content();
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
	thisNode = new ObjectOperandNode(variable, currentToken->Content());
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
	thisNode = new HashOperandNode(currentToken->Content());
    ConsumeToken();
  }
  return thisNode;
}

AddressOperandNode *Parser::MatchAddressOperand() {
  AddressOperandNode *thisNode = NULL;
  if(TokenIs(AddressString)) {
	thisNode = new AddressOperandNode( currentToken->Content() );
    ConsumeToken();
  }
  return thisNode;
}

IndirectOperandNode *Parser::MatchIndirectOperand() {
  TokenIterator savedCurr = currentToken;
  IndirectOperandNode *thisNode = NULL;
  IndirectOperandTermNode *termNode = NULL;

  if( TokenIsNot(LeftSquare) ) return NULL;
  ConsumeToken();

  if( TokenIsNot(Identifier) ) {
    // TODO: Raise syntax error
    ResetTokenPosition( savedCurr );
    return NULL;
  }

  thisNode = new IndirectOperandNode(currentToken->Content());
  ConsumeToken();

  while((termNode = MatchIndirectOperandTerm())) {
    thisNode->AppendOperand(termNode);
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

IndirectOperandTermNode *Parser::MatchIndirectOperandTerm() {
  TokenIterator savedCurr = currentToken;
  IndirectOperandTermNode *thisNode = NULL;
  ASTNode *value = NULL;

  if( TokenIsNot( Plus ) &&
      TokenIsNot( Minus ) &&
      TokenIsNot( Multiply ) ) {
    return NULL;
  }

  thisNode = new IndirectOperandTermNode( currentToken->Content() );
  ConsumeToken();

  if( TokenIs(Integer) ) {
	value = new IntegerLiteralNode( currentToken->Content() );
    ConsumeToken();
    thisNode->AppendChild( value );
    return thisNode;
  } else if ( TokenIs(Identifier) ) {
	value = new DirectOperandNode( currentToken->Content() );
    ConsumeToken();
    thisNode->AppendChild( value );
    return thisNode;
  } else {
    ResetTokenPosition( savedCurr );
    delete thisNode;
    return NULL;
  }
}
