#ifndef __SOURCE_FILE_H
#define __SOURCE_FILE_H

#include <string>
#include <list>
#include <stack>
#include <set>
#include "token.hpp"
#include "i386/assembly_block.h"

class ASTNode;
class Scope;

typedef std::set<std::string> SymbolTable;

class SourceFile {
  friend class Lexer;
public:
  SourceFile( std::string );
  ~SourceFile();
  void Tokenize();
  void Parse();
  void Analyse();
  void GenerateCode();
  void PrintTokens();
  void PrintAST();
  void PrintAsm();
  void AddExternSymbol(std::string);
  std::list<Token>& GetTokenStream() { return tokenStream; }
  std::stack<int> indentStack;
private:
  std::string fileName;
  std::list<Token> tokenStream;
  ASTNode *astRoot;
  Scope *lobby;
  AssemblyBlock *assembly;
  SymbolTable externSymbols;
};

#endif
