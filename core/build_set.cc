#include <fstream>
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
		i->PrintAsm(std::cout);
		i++;
	}

	while(i != end) {
		i->GenerateCode();
		i++;
	}
}

bool BuildSet::Assemble()
{
	SourceFileIterator i = files.begin();
	SourceFileIterator end = files.end();
	std::ofstream asmFile;
	bool allGood = true;

	while(i != end) {
		std::string asmFileName = BaseWorkingDirectory() + ASM_DIRECTORY + i->BaseFileName() + ".asm";
		asmFile.open(asmFileName.c_str(), std::ios::out);
		i->PrintAsm(asmFile);
		asmFile.close();

		std::string objFileName = BaseWorkingDirectory() + OBJ_DIRECTORY + i->BaseFileName() + ".o";
		// -O1 required to get NASM to resize short jumps to near jumps
		std::string cmd = "nasm " + asmFileName + " -fmacho -O1 -o " + objFileName;

		int result = system(cmd.c_str());

		if (result != 0) {
			std::cerr << "NASM returned non-zero error code while assembling " + asmFileName + "\n";
			allGood = false;
		}

		i++;
	}

	return allGood;
}

bool BuildSet::Link(std::string target)
{
	SourceFileIterator i = files.begin();
	SourceFileIterator end = files.end();
	std::string cmd = "ld ";

	while(i != end) {
		std::string objFileName = BaseWorkingDirectory() + OBJ_DIRECTORY + i->BaseFileName() + ".o";
		cmd += objFileName;
		cmd += " ";

		i++;
	}

	cmd += " -lc -o ";
	cmd += target;

	return system(cmd.c_str());;
}

