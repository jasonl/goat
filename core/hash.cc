#include <stdint.h>

#include "goat.h"
#include "ast_node.h"

// This is an implementation of the Foller/Noll/Vo Hash algorithm
// described at:
//
// http://isthe.com/chongo/tech/comp/fnv/
//
// As this algorithm is in the public domain, the code in this file
// is also placed in the public domain.

#define FNV_PRIME 0x01000193
#define FNV1_32_INIT 0x811c9dc5

Hash goatHash( std::string data ) {
  Hash hval = FNV1_32_INIT;

  for(size_t i = 0; i < data.length(); ++i) {
    hval *= FNV_PRIME;
    hval ^= (Hash)data[i];
  }

  return hval;
}
