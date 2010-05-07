#include "token.hpp"

Token::Token( TokenType _type ) : type(_type) {
  content = "";
}

Token::Token( TokenType _type, std::string _content="" ):
  type(_type), content(_content) { }
