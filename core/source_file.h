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

typedef struct {
  std::string contents;
  std::string label;
} StringData;

class SourceFile {
  friend class Lexer;
public:
  SourceFile( std::string, bool );
  ~SourceFile();
  void Tokenize();
  void Parse();
  void Analyse();
  void GenerateCode();
  void PrintTokens();
  void PrintAST();
  void PrintAsm();
  void AddExternSymbol(std::string);
  std::string AddString(std::string);
  bool IsLibrary() { return isLibrary; }

  std::list<Token>& GetTokenStream() { return tokenStream; }
  std::stack<int> indentStack;
private:
  std::string fileName;
  std::list<Token> tokenStream;
  std::list<StringData> strings;
  ASTNode *astRoot;
  Scope *lobby;
  AssemblyBlock *assembly;
  SymbolTable externSymbols;
  bool isLibrary;
  int strCounter;
};

#endif
