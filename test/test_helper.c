#include <stdio.h>
#include "test.h"

void assert( int condition, char* message) {
  if(condition) {
    printf(".");
  } else {
    printf("Test Failed: %s\n", message);
  }
}
