#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main(int argc, char *argv[]) {
  for (int i = 1; i <= 10; i++) {
    printf("%d\n", i);
  }

  pid_t ret = pfork();
  if (ret == 0) {
    pexecl("./counter1_child", "./counter1_child", NULL);
  } else {
    pwait(NULL);
  }
}
