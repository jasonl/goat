#ifndef __BUILD_SET_H
#define __BUILD_SET_H

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include "source_file.h"

#define ASM_DIRECTORY "/asm/"
#define OBJ_DIRECTORY "/o/"

typedef std::list<SourceFile>::iterator SourceFileIterator;
typedef std::set<std::string> Namespace;

class BuildSet
{
 public:
	BuildSet() {};
	void AddSourceFile(SourceFile&);
	void Tokenize(bool);
	void Parse();
	void Analyse(bool);
	void GenerateCode(bool);
	bool Assemble();
	bool Link(std::string);
	void RegisterClass(std::string);
	bool ClassExists(std::string);
	void RegisterSingleton(std::string);
	bool SingletonExists(std::string);
	Namespace::iterator FirstSingleton() { return singletonNames.begin(); }
	Namespace::iterator LastSingleton() { return singletonNames.end(); }
	// TODO: Make this relative to the source-file
	std::string BaseWorkingDirectory() { return "/Users/jason/Code/goat/.goat"; }
 private:
	std::list<SourceFile> files;
	Namespace classNames;
	Namespace singletonNames;
};

#endif
