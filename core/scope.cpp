#include <string>
#include <sstream>
#include "scope.h"
#include "variable.h"

/*
  
  A scope object represents a lexical scope.
  
  The four different types of variables are:

  - Global Variables ( at a fixed address )
  - Parameter Variables ( relative to EBP with a positive offset )
  - Local Variables ( relative to EBP with a negative offset )
  - Instance Variables ( relative to ECX with a positive offset )

*/

Scope::Scope( Scope* parent ) {
  // Set the parent scope, for example the enclosing
  // function around an anonymous lambda, or the class
  // scope around a method.
  enclosingScope = parent;
  firstVariable = NULL;
  uniqueVal = 0;
  variableCount = 0;
  nextScope = NULL;
  firstChildScope = NULL;

  if( parent ) {
    parent->RegisterChildScope( this );
  }
}

Scope::~Scope() {
  Variable *lastVariable = firstVariable, *tempVariable = NULL;
  Scope *lastScope = firstChildScope, *tempScope = NULL;

  while(lastVariable) {
    tempVariable = lastVariable->next;
    delete lastVariable;
    lastVariable = tempVariable;
  }

  while(lastScope) {
    tempScope = lastScope->nextScope;
    delete lastScope;
    lastScope = tempScope;
  }
}

void Scope::RegisterChildScope( Scope *newChild ) {
  Scope *lastChild = firstChildScope;

  if (firstChildScope) {
    while(lastChild->nextScope) {lastChild = lastChild->nextScope; }
    lastChild->nextScope = newChild;
  } else {
    firstChildScope = newChild;
  }
}

void Scope::AddParameterVariable( std::string name ) {
  Variable *lastVar = NULL, *newVar = new Variable( name );
  
  if(firstVariable == NULL) {
    newVar->ebpOffset = 0;
    firstVariable = newVar;
  } else {
    lastVar = firstVariable;
    while( lastVar->next ) { lastVar = lastVar->next; }
    lastVar->next = newVar;
    
    newVar->ebpOffset = lastVar->ebpOffset + OBJECT_SIZE;
  }

  variableCount++;
}

void Scope::AddClassVariable( std::string name ) {
  // TODO
}

void Scope::AddLocalVariable( std::string name ) {
  Variable *lastVar = NULL, *newVar = new Variable( name ), *cursorVar;
  
  if (firstVariable == NULL) {
    newVar->ebpOffset = -4 - OBJECT_SIZE; // As EBP is pushed onto the stack
    firstVariable = newVar;
  } else {    
    cursorVar = firstVariable;
    
    while( cursorVar ) {
      lastVar = cursorVar;
      cursorVar = cursorVar->next;
    }
    
    lastVar->next = newVar;
    //TODO: Abstract stack growth direction out of this.
    newVar->ebpOffset = lastVar->ebpOffset - OBJECT_SIZE;
  }

  variableCount++;
}

bool Scope::HasVariable( std::string name ) {
  return (FindVariable(name) ? true : false); 
}

Variable *Scope::FindVariable( std::string name ) {
  Variable *lastVar = firstVariable;

  while (lastVar) {
    if (lastVar->name == name) return lastVar;
    lastVar = lastVar->next;
  }
  
  // TODO: Work out how access to variables in higher scopes,
  // for closures.

  return NULL;
}

bool Scope::HasParameterVariable( std::string name ) {
  // TODO: Yes, this may require logic..
  return true;
}

// Generates the assembly operand pointing to the variable's
// payload. Note this does not add a size specifier to the 
// Operand, so this must be done by the caller, for example
// when pushing an operand's value onto the stack.
Operand &Scope::GeneratePayloadOperand( std::string name ) {  
  Variable *var = FindVariable(name);
    
  if(var) {
    return _[ebp + (var->ebpOffset + PAYLOAD_OFFSET)];
  } else {
    return eax;
  }
}

// Generates the assembly operand pointing to the variable's
// type hash. Does not add an operand size specifier
Operand &Scope::GenerateTypeHashOperand( std::string name ) {
  Variable *var = FindVariable(name);
    
  if(var) {
    return _[ebp + (var->ebpOffset + TYPE_HASH_OFFSET)];
  } else {
    return eax;
  }
}

// Generates the assembly operand pointing to the variable's
// dispatch function. Does not add an operand size specifier.
Operand &Scope::GenerateDispatchOperand( std::string name ) {
  Variable *var = FindVariable(name);
    
  if(var) {
    return _[ebp + (var->ebpOffset + DISPATCH_OFFSET)];
  } else {
    return eax;
  }
}

// Generates a string which is guaranteed to be unique across
// all files.
std::string Scope::GenerateUniqueLabel( std::string _base ) {
  std::stringstream s;
  s << (unsigned long) this << '_' << uniqueVal << '_' << _base;
  uniqueVal++;
  return s.str();
}
