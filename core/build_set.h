#ifndef __BUILD_SET_H
#define __BUILD_SET_H

#include <list>
#include "source_file.h"

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
 private:
	std::list<SourceFile> files;
};

#endif
