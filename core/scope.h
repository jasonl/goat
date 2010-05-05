//
// scope.h
//
// Class definition for a lexical scope, including
// symbol table. 

// An offset is relative to EBP, so in any given function
// is positive for parameters passed to a function, and 
// negative for local variables allocated on the stack.

#ifndef __SCOPE_H
#define __SCOPE_H

typedef signed long offset;

// A variable allocated in any given scope.
class Variable;

// Object size is the number of bytes we allocate for an object itself,
// excluding its payload. In our case, this is 12 bytes:
// 32-bit hash of the object type
// 32-bit absolute offset of the dispatch function
// 32-bit payload (either an actual value, or a pointer to data)
#define OBJECT_SIZE 12

// Within each object, we have offsets for the various pieces of information
#define TYPE_HASH_OFFSET 0
#define DISPATCH_OFFSET 4
#define PAYLOAD_OFFSET 8

// A Scope is a lexical scope, in which variables
// are allocated. It is a spaghetti stack type of structure,
// where variable names are recursively searched up the stack
// to be resolved. 

class Scope {
 public:
  Scope( Scope* );
  ~Scope();
  void AddStackVariable( char* );
  void AddParameterVariable( char* );
  void AddClassVariable( char* );
  bool HasVariable( char* );
  offset GetVariableOffset( char* ); 
  offset GetTypeHashOffset( char* );
  offset GetDispatchOffset( char* );
  offset GetPayloadOffset( char* );
 private:
  Scope *enclosingScope;
  Variable *firstVariable;
};

#endif
