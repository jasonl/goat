#include <string>
#include "scope.h"
#include "variable.h"

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

/*void Scope::AddParameterVariable( char *name ) {
  
  }*/

void Scope::AddStackVariable( char *name ) {
  Variable *lastVar = NULL, *newVar = new Variable( std::string(name) ), *cursorVar;
  
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

bool Scope::HasVariable( char *name ) {
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
