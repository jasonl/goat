#ifndef __SOURCE_FILE_H
#define __SOURCE_FILE_H

#include <string>
#include <list>
#include <stack>
#include "token.hpp"

class ASTNode;
class Scope;

class SourceFile {
  friend class Lexer;
public:
  SourceFile( std::string );
  ~SourceFile();
  void Tokenize();
  void Parse();
  void Analyse();
  void PrintTokens();
  void PrintAST();
  std::list<Token>& GetTokenStream() { return tokenStream; }
  std::stack<int> indentStack;
private:
  std::string fileName;
  std::list<Token> tokenStream;
  ASTNode *astRoot;
  Scope *lobby;
};

#endif
