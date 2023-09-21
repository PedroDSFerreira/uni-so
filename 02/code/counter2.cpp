#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main(int argc, char *argv[]) {
  pid_t ret = pfork();
  if (ret == 0) {
    for (int i = 1; i <= 10; i++) {
      printf("%d\n", i);
    }
  } else {
    pwait(NULL);
    for (int i = 11; i <= 20; i++) {
      printf("%d\n", i);
    }
  }
}
