#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>
#include <list>

enum TokenType { RightParen, LeftParen,
		 Lambda, Colon, Period, Comma, Equals,
		 Identifier, Integer, String,
		 If, Else, Return, End, New, Asm,
		 Class, Include,
		 Indent, IndentIncrease, IndentDecrease,
		 Newline, Whitespace, Comment,
		 EndOfFile,

		 // Assembly-only tokens
		 RightSquare, LeftSquare,
		 Plus, Minus, Multiply,
		 HashString, AddressString,
		 Label
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
