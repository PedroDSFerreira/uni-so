#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main(int argc, char *argv[]) {
  for (int i = 11; i <= 20; i++) {
    printf("%d\n", i);
  }
}
