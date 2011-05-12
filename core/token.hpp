#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>
#include <list>

enum TokenType {
	Asm,
	Class,
	ClassVar,
	Colon,
	Comma,
	Comment,
	Else,
	End,
	EndOfFile,
	Equals,
	Identifier,
	If,
	Include,
	Indent,
	IndentDecrease,
	IndentIncrease,
	Integer,
	Lambda,
	LeftParen,
	New,
	Newline,
	Period,
	Return,
	RightParen,
	String,
	Whitespace,

	// Assembly-only tokens
	AddressString,
	HashString,
	Label,
	LeftSquare,
	Minus,
	Multiply,
	Plus,
	RightSquare
};

class Token {
public:
  Token( TokenType );
  Token( TokenType, std::string );
  void SetContent( std::string _content ) { content = _content; }
  std::string Content() const { return content; }
  void ClearContent() { content.clear(); }
  void SetLineNumber( int _lineNumber ) { lineNumber = _lineNumber; }
  int LineNumber() { return lineNumber; }
  TokenType Type() { return type; }
  void SetType( TokenType _type ) { type = _type; }
	void TransformKeyword(std::string, TokenType);
private:
  TokenType type;
  int lineNumber;
  std::string content;
};

typedef std::list<Token>::iterator TokenIterator;

#endif
