#include "process.h"
#include <stdio.h>

int main(void) {
  printf("Input PID: ");
  int pid;
  scanf("%d", &pid);
  pkill((pid_t)pid, 2);
  return 0;
}
