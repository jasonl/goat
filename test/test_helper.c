#include <stdio.h>
#include "test.h"

void assert( int condition, char* message) {
  char failure[] = "\x1b[1;33mTest Failed\x1b[0;37;00m:";

  if(condition) {
    printf(".");
  } else {
    printf("\n%s %s", failure, message);
  }
}
