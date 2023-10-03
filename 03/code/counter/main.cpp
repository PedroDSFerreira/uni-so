#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "process.h"

int main(int argc, char *argv[]) {
  // creation:
  int shmid = pshmget(IPC_PRIVATE, sizeof(int), 0600 | IPC_CREAT | IPC_EXCL);
  // attach shm to pointer address:
  int *pcounter = (int *)pshmat(shmid, NULL, 0);
  *pcounter = 0;

  if (pfork() == 0) {
    // child
    int max;
    printf("Enter max [10:20]: ");
    scanf("%d", &max);
    assert(max > 10);
    assert(max <= 20);

    while (*pcounter < max) {
      (*pcounter)++;
      printf("\nChild: %d", *pcounter);
      sleep(1);
    }
    exit(EXIT_SUCCESS);
  } else {
    // parent
    pwait(NULL);

    while (*pcounter > 1) {
      (*pcounter)--;
      printf("\nParent: %d", *pcounter);
      sleep(1);
    }
  }

  // detach shm from pointer address:
  pshmdt(pcounter);
  // destroy shm:
  pshmctl(shmid, IPC_RMID, NULL);
}
