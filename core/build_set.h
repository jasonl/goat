#ifndef __BUILD_SET_H
#define __BUILD_SET_H

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "source_file.h"

#define ASM_DIRECTORY "/asm/"
#define OBJ_DIRECTORY "/o/"

typedef std::list<SourceFile>::iterator SourceFileIterator;

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
	std::string BaseWorkingDirectory() { return "/Users/jason/Code/goat/.goat"; }
 private:
	std::list<SourceFile> files;
};

#endif
