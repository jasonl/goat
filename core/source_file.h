#ifndef __SOURCE_FILE_H
#define __SOURCE_FILE_H

#include <string>
#include <list>
#include <stack>
#include <set>
#include <iostream>
#include "token.hpp"
#include "i386/assembly_block.h"

class ASTNode;
class Scope;
class BuildSet;

typedef std::set<std::string> SymbolTable;

typedef struct {
  std::string contents;
  std::string label;
} StringData;

class SourceFile {
  friend class Lexer;
public:
  SourceFile(std::string, bool);
  ~SourceFile();
  void Tokenize();
  void Parse();
  void ParseOntoNode(ASTNode*);
  void RetainAST();
  void Analyse();
  void GenerateCode();
  void PrintTokens();
  void PrintAST();
  void PrintAsm(std::ostream&);
  void AddExternSymbol(std::string);
  void AddGlobalSymbol(std::string);
  void RegisterClass(std::string);
  bool ClassExists(std::string);
  void RegisterSingleton(std::string);
  bool SingletonExists(std::string);
  std::string AddString(std::string);
  std::string ResolveIncludedFile(const std::string&) const;
  bool IsLibrary() { return isLibrary; }
  void SetBuildSet(BuildSet *bs) { buildSet = bs; }
  BuildSet* GetBuildSet() { return buildSet; }
  TokenIterator FirstToken() { return tokenStream.begin(); };
  TokenIterator LastToken() { return tokenStream.end(); };
  std::list<Token>& GetTokenStream() { return tokenStream; }
  std::stack<int> indentStack;
  std::string BaseFileName() const;
  std::string FileName() const { return fileName; }
#ifdef GOATTEST
  void AddToken(Token& _token) {
	  tokenStream.push_back(_token);
  };
#endif
private:
  std::string fileName;
  std::list<Token> tokenStream;
  // A place to keep tokens when copied from SourceFiles which might
  // go out of scope.
  std::list<Token> auxillaryTokens;
  std::list<StringData> strings;
  ASTNode *astRoot;
  Scope *lobby;
  AssemblyBlock *assembly;
  SymbolTable externSymbols;
  SymbolTable globalSymbols;
  bool isLibrary;
  int strCounter;
  BuildSet *buildSet;
};

#endif
