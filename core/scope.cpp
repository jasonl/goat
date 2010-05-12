#include <string>
#include "scope.h"
#include "variable.h"

/*
  
  A scope object represents a lexical scope.
  
  The four different types of variables are:

  - Global Variables ( at a fixed address )
  - Parameter Variables ( relative to EBP with a positive offset )
  - Stack Variables ( relative to EBP with a negative offset )
  - Instance Variables ( relative to ECX with a positive offset )

*/

Scope::Scope( Scope* parent ) {
  // Set the parent scope, for example the enclosing
  // function around an anonymous lambda, or the class
  // scope around a method.
  enclosingScope = parent;
  firstVariable = NULL;
}

Scope::~Scope() {
  Variable *lastVariable = firstVariable, *tempVariable = NULL;

  while(lastVariable) {
    tempVariable = lastVariable->next;
    delete lastVariable;
    lastVariable = tempVariable;
  }
}

void Scope::AddParameterVariable( std::string name ) {
  // TODO
}

void Scope::AddClassVariable( std::string name ) {
  // TODO
}

void Scope::AddStackVariable( std::string name ) {
  Variable *lastVar = NULL, *newVar = new Variable( name ), *cursorVar;
  
  if (firstVariable == NULL) {
    newVar->ebpOffset = 0;
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
}

bool Scope::HasVariable( std::string name ) {
  Variable *lastVar = firstVariable;

  while (lastVar) {
    if (lastVar->name == name) return true;
    lastVar = lastVar->next;
  }
  
  if (enclosingScope) {
    return enclosingScope->HasVariable( name );
  }

  return false;
}

bool Scope::HasParameterVariable( std::string name ) {
  // TODO: Yes, this may require logic..
  return true;
}

// It is the callers responsibility to ensure there is
// a variable in the scope by calling HasVariable. 
offset Scope::GetVariableOffset( char* name ) {
  Variable *lastVar = firstVariable;

  while (lastVar) {
    if (lastVar->name == name) return lastVar->ebpOffset;
    lastVar = lastVar->next;
  }
  
  if (enclosingScope) {
    return enclosingScope->GetVariableOffset( name );
  }

  //TODO: Add exception
  return NULL;
}

offset Scope::GetTypeHashOffset( char* name ) {
  return GetVariableOffset( name ) - TYPE_HASH_OFFSET;
}

offset Scope::GetDispatchOffset( char* name ) {
  return GetVariableOffset( name ) - DISPATCH_OFFSET;
}

offset Scope::GetPayloadOffset( char* name ) {
  return GetVariableOffset( name ) - PAYLOAD_OFFSET;
}
