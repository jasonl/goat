#ifndef __DISPATCH_FUNCTION_H
#define __DISPATCH_FUNCTION_H

typedef std::map<std::string, std::string> DispatchMap;
typedef std::map<std::string, std::string>::const_iterator DispatchMapIterator;

class DispatchFunction
{
  public:
	void AddMethod(std::string, std::string);
	void GenerateDispatchAssembly(AssemblyBlock*) const;
  private:
	 DispatchMap methods;
};

#endif
