#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "process.h"

int main(void) {
  printf("Input PID: ");
  int pid;
  scanf("%d", &pid);
  pkill((pid_t)pid, SIGINT);
  return 0;
}
