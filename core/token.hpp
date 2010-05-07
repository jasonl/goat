#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>

enum TokenType { RightParen, LeftParen,
		 Lambda, Colon, Period, Comma, Equals,
		 Identifier, Integer, String,
		 If, Else, Return, End, New,
		 Class,
		 Indent, IndentIncrease, IndentDecrease, 
		 Newline, Whitespace, Comment,
		 EndOfFile };

class Token {
public:
  Token( TokenType );
  Token( TokenType, std::string );
  void SetContent( std::string _content ) { content = _content; }
  std::string Content() { return content; }
  void ClearContent() { content.clear(); }
  void SetLineNumber( int _lineNumber ) { lineNumber = _lineNumber; }
  int LineNumber() { return lineNumber; }
  TokenType Type() { return type; }
  void SetType( TokenType _type ) { type = _type; }
private:
  TokenType type;
  int lineNumber;
  std::string content;
  Token *next;
};

#endif
