#include "build_set.h"

void BuildSet::AddSourceFile(SourceFile& sourceFile)
{
	files.push_back(sourceFile);
}

void BuildSet::Tokenize(bool printFirst)
{
	SourceFileIterator i = files.begin();
	SourceFileIterator end = files.end();

	// If there's a first SourceFile, print it
	if(printFirst && i != end) {
		i->Tokenize();
		i->PrintTokens();
		i++;
	}

	while(i != end) {
		i->Tokenize();
		i++;
	}
}

void BuildSet::Parse()
{
	SourceFileIterator i = files.begin();
	SourceFileIterator end = files.end();

	while(i != end) {
		i->Parse();
		i++;
	}
}

void BuildSet::Analyse(bool printFirst)
{
	SourceFileIterator i = files.begin();
	SourceFileIterator end = files.end();

	// If there's a first SourceFile, print it
	if(printFirst && i != end) {
		i->Analyse();
		i->PrintAST();
		i++;
	}

	while(i != end) {
		i->Analyse();
		i++;
	}
}

void BuildSet::GenerateCode(bool printFirst)
{
	SourceFileIterator i = files.begin();
	SourceFileIterator end = files.end();

	// If there's a first SourceFile, print it
	if(printFirst && i != end) {
		i->GenerateCode();
		i->PrintAsm();
		i++;
	}

	while(i != end) {
		i->Analyse();
		i++;
	}
}



