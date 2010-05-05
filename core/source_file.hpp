#ifndef __SOURCE_FILE_H
#define __SOURCE_FILE_H

#include <string>

class ASTNode;
class Scope;

class SourceFile {
public:
  SourceFile( std::string );
  ~SourceFile();
  void Tokenize();
  void Parse();
  void Analyse();
  void PrintTokens();
  void PrintAST();
private:
  std::string fileName;
  Token *tokenStream;
  ASTNode *astRoot;
  Scope *lobby;
};

#endif
