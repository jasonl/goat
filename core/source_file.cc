#include <iostream>
#include <sstream>
#include <cstdio>
#include <fcntl.h>
#include <cstring> // For memset
#include <sys/mman.h> // For mmap
#include <sys/stat.h>

#include "goat.h"
#include "ast_node.h"
#include "lexer.h"
#include "scope.h"
#include "parser.h"
#include "source_file.h"
#include "build_set.h"

extern std::string libraryDirectory;

SourceFile::SourceFile( std::string _fileName, bool _isLibrary ) {
  fileName = _fileName;
  isLibrary = _isLibrary;
  astRoot = NULL;
  lobby = NULL;
  assembly = NULL;
  indentStack.push(0);
  strCounter = 0;
}

SourceFile::~SourceFile() {
  // Free the AST
  if( astRoot ) delete astRoot;

  // Free the Scope tree
  // TODO - We need to iterate over all scopes somehow
  if( lobby ) delete lobby;
}

void SourceFile::Tokenize() {
  int fp;
  size_t size;
  struct stat sb;
  char *start, *end;

  fp = open(fileName.c_str(), O_RDONLY);

  // Get the file size
  if(fstat(fp, &sb) == -1) {
    printf("Error getting file stat");
    return;
  }
  size = sb.st_size;

  start = (char *) mmap( NULL, size, PROT_READ, MAP_SHARED, fp, 0);
  end = start + size;

  if( start == MAP_FAILED ) {
    printf("Map failed\n");
  }

  Lexer lexer( start, end, this );
  lexer.Lex();
}

// Parse()
// Transforms the stream of tokens into an Abstract Syntax Tree
void SourceFile::Parse() {
  astRoot = new SourceFileNode;
  ParseOntoNode(astRoot);
}

void SourceFile::ParseOntoNode( ASTNode *baseNode ) {
  if( !tokenStream.empty() ) {
	  Parser parser(this);
	  parser.Parse(baseNode);
  } else {
    std::cerr << "Unable to parse source file. No tokens found";
  }
}

void SourceFile::RetainAST() {
	// This ensures the AST won't be deleted when the destructor is called.
	astRoot = NULL;
}

void SourceFile::Analyse() {
  lobby = new Scope( this );

  if( astRoot ) {
    astRoot->Analyse( lobby );
  } else {
    std::cerr << "No Abstract Syntax Tree was built from this source file";
  }
}

void SourceFile::GenerateCode() {
  if( astRoot ) {
    assembly = astRoot->GenerateCode();
    assembly->AppendBlock(astRoot->GetAuxiliaryCode());

    for( SymbolTable::iterator i = externSymbols.begin(); i != externSymbols.end(); i++) {
		if(globalSymbols.count(*i) == 0) {
			assembly->AppendItem(new ExternSymbol(*i));
		}
    }

    assembly->SetSegment(".data");

    for( std::list<StringData>::iterator i = strings.begin(); i != strings.end(); i++) {
      assembly->dw((*i).contents.length());
      assembly->db((*i).contents);
      assembly->LabelLastInstruction((*i).label );
    }

  } else {
    std::cerr << "No Abstract Syntax Tree was built from this source file";
  }
}

void SourceFile::PrintTokens() {
  std::list<Token>::iterator curr = tokenStream.begin();

  std::cout << "Token List\n";

  for( std::list<Token>::iterator curr = tokenStream.begin(); curr != tokenStream.end(); curr++) {
    std::cout << curr->LineNumber() << " ";
    switch( curr->Type() )
      {
      case Indent:            std::cout << "Indent         "; break;
      case Comment:           std::cout << "Comment        "; break;
      case IndentIncrease:    std::cout << "IndentIncrease "; break;
      case IndentDecrease:    std::cout << "IndentDecrease "; break;
      case Comma:             std::cout << "Comma          "; break;
      case Period:            std::cout << "Period         "; break;
      case Lambda:            std::cout << "Lambda         "; break;
      case Colon:             std::cout << "Colon          "; break;
      case RightParen:        std::cout << "RightParen     "; break;
      case LeftParen:         std::cout << "LeftParen      "; break;
      case Equals:            std::cout << "Equals         "; break;
      case Integer:           std::cout << "Integer        "; break;
      case String:            std::cout << "String         "; break;
      case Identifier:        std::cout << "Identifier     "; break;
      case EndOfFile:         std::cout << "EndOfFile      "; break;
      case Newline:           std::cout << "Newline        "; break;
      case Whitespace:        std::cout << "WhiteSpace     "; break;
      case If:                std::cout << "If             "; break;
      case Else:              std::cout << "Else           "; break;
      case Return:            std::cout << "Return         "; break;
      case Class:             std::cout << "Class          "; break;
      case Asm:               std::cout << "Asm            "; break;
	// Assembly Tokens
      case Plus:              std::cout << "Plus           "; break;
      case Minus:             std::cout << "Minus          "; break;
      case Multiply:          std::cout << "Multiply       "; break;
      case Label:             std::cout << "Label          "; break;
      case HashString:        std::cout << "HashString     "; break;
      case AddressString:     std::cout << "AddressString  "; break;
      default:                std::cout << curr->Type();        break;
      }

    switch( curr->Type() )
      {
      case Integer:
      case String:
      case Identifier:
      case Label:
      case HashString:
      case AddressString:
	std::cout << curr->Content();
	break;
      default:
	break;
      }

    std::cout << "\n";
    }
}

void SourceFile::PrintAST() {
  char prev_cols[100];

  if( astRoot ) {
    memset( prev_cols, 0, 100 );
    astRoot->print( 0, 0, prev_cols );
  } else {
    std::cout << "No AST Nodes found.\n";
  }
}

void SourceFile::PrintAsm(std::ostream &stream) {
  AssemblerItemIterator end(NULL);

  if( assembly ) {
    for(AssemblerItemIterator i = assembly->Instructions(); i != end; i++) {
      stream << *i << "\n";
    }
  }
}

void SourceFile::RegisterClass(std::string className)
{
	buildSet->RegisterClass(className);
}

bool SourceFile::ClassExists(std::string className)
{
	return buildSet->ClassExists(className);
}

void SourceFile::RegisterSingleton(std::string singletonName)
{
	buildSet->RegisterSingleton(singletonName);
}

bool SourceFile::SingletonExists(std::string singletonName)
{
	return buildSet->SingletonExists(singletonName);
}

void SourceFile::AddExternSymbol( std::string symbol) {
  externSymbols.insert(symbol);
}

void SourceFile::AddGlobalSymbol(std::string symbol)
{
	globalSymbols.insert(symbol);
}

std::string SourceFile::AddString( std::string _string ) {
  StringData sd;
  std::stringstream label;

  label << "str" << strCounter;

  sd.contents = _string;
  sd.label = label.str();

  strings.push_back(sd);
  strCounter++;

  return label.str();
}

std::string SourceFile::ResolveIncludedFile(const std::string &relativePath) const
{
	std::string thisDirectory = GetBaseDirectory(fileName.c_str());
	std::string relativeInclude = thisDirectory + "/" + relativePath;

	if(FileExists(relativeInclude))
		return relativeInclude;

	std::string libraryInclude = libraryDirectory + "/" + relativePath;

	if(FileExists(libraryInclude))
		return libraryInclude;

	goatFatalError("Unable to find included file '" + relativePath + "'");
	return "";
}

std::string SourceFile::BaseFileName() const
{
	return GetBaseFileName(fileName.c_str());
}
