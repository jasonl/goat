/*
 * File:   goat.c
 * Author: Jason Langenauer
 *
 * Created on 12 November 2009, 6:15 PM
 */
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#include <string.h>
#include <libgen.h>

#include "goat.h"
#include "build_set.h"
#include "lexer.h"
#include "ast_node.h"
#include "parser.h"
#include "source_file.h"

std::string libraryDirectory;

#ifndef GOATTEST
int main(int argc, char** argv) {
  int verbose = 0;
  bool library = false;
  std::string sourceFileName;
  BuildSet buildSet;

  sourceFileName = parseCommandLine( argc, argv, &verbose, &library );

  SourceFile sourceFile( sourceFileName, library );

  buildSet.AddSourceFile(sourceFile);

  buildSet.Tokenize(verbose & VERBOSE_TOKENS);
  buildSet.Parse();
  buildSet.Analyse(verbose & VERBOSE_AST);
  buildSet.GenerateCode(verbose & VERBOSE_ASM);
  buildSet.Assemble();
  buildSet.Link("a.out");
  return EXIT_SUCCESS;
}
#endif

void goatFatalError( const std::string msg ) {
  std::cerr << "FATAL ERROR: %s\n" << msg;
  exit(1);
}

#ifndef TEST

// We don't use this during tests so we can replace this function with
// an mocked goatError() to allow us to test that errors are raised. It's
// in test/test_helper.c
void goatError( int lineNo, const std::string fmt, ... ) {
  va_list arg;
  va_start( arg, fmt );
  std::cout << "\x1b[1;31mError\x1b[0;37;00m[" << lineNo << "]";
  vfprintf( stdout, fmt.c_str(), arg );
  std::cout << "\n";
  va_end(arg);
}

#endif

std::string GetBaseDirectory(const char *relativePath)
{
  char *currentWorkingDir = getcwd(NULL, 0);
  char *realBaseCommand;
  std::string baseDir;

  if(relativePath[0] == '/') {
	  // When running under GDB, the relative path is the full path. Who knows why.
	  realBaseCommand = realpath(relativePath, NULL);
  } else {
	  // Generate the full path of the goatc executable
	  std::string fullPath(std::string(currentWorkingDir) + "/" + std::string(relativePath));

	  // And strip of the directory
	  realBaseCommand = realpath(fullPath.c_str(), NULL);
  }

  baseDir = realBaseCommand;
  free(realBaseCommand);
  free(currentWorkingDir);

  return baseDir.substr(0, baseDir.find_last_of('/'));
}

// Returns the name of the file, without extension.
std::string GetBaseFileName(const char *relativePath)
{
	std::string baseName(basename(const_cast<char*>(relativePath)));

	size_t pos = baseName.rfind(".");
    if(pos == std::string::npos)  //No extension.
        return baseName;

    if(pos == 0)    //. is at the front. Not an extension.
        return baseName;

    return baseName.substr(0, pos);
}

bool FileExists(const std::string &fileName)
{
	return (access(fileName.c_str(), R_OK) != -1);
}

std::string parseCommandLine( int argc, char *argv[], int *verbose, bool *library) {
  int i;
  std::string fileName;

  libraryDirectory = GetBaseDirectory(argv[0]) + "/lib";

  if (argc == 1) {
    std::cerr << "Goat - An experimental language\n";
    std::cerr << "-------------------------------\n\n";
    std::cerr << "Correct usage:\n";
    std::cerr << "goat <options> input_file.gt\n\n";
    std::cerr << "options:\n";
    std::cerr << "-vlex              Print token stream.\n";
    std::cerr << "-vtree             Print AST.\n";
    std::cerr << "-vasm              Print generated assembly.\n";
    std::cerr << "-l                 Compile as library.\n";
    exit(1);
  }

  for ( i=1; i <= (argc - 1); ++i) {

    if(argv[i][0] == '-') {
      // Option switch
      switch( argv[i][1] ){
      case 'L':
      case 'l':
	*library = true;
	break;
      case 'V':
      case 'v':
	switch( argv[i][2] ){
	// -vTree - print the AST
	case 't':
	case 'T':
	  *verbose |= VERBOSE_AST;
	  break;
	// -vLex - print lexical token stream
	case 'l':
	case 'L':
	  *verbose |= VERBOSE_TOKENS;
	  break;
	// -vScope - print scopes
	case 'S':
	case 's':
	  *verbose |= VERBOSE_SCOPES;
	  break;
	  // -vAsm - print assembly
	case 'm':
	case 'M':
	  *verbose |= VERBOSE_ASM;
	break;
	  }
	break;
      default:
	std::cerr << "Invalid option: " << argv[i] << "\n";
	exit(0);
      }
    }
    else {
      // Input file
      fileName = argv[i];
    }
  }

  return fileName;
}
