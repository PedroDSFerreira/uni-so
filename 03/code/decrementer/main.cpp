#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "process.h"

#define N_PROC 2

int main(int argc, char *argv[]) {
  // creation:
  int shmid = pshmget(IPC_PRIVATE, sizeof(int), 0600 | IPC_CREAT | IPC_EXCL);
  // attach shm to pointer address:
  int *pcounter = (int *)pshmat(shmid, NULL, 0);
  int num;
  printf("Enter max [10:20]: ");
  scanf("%d", &num);

  if (num < 10 || num > 20) {
    exit(EXIT_FAILURE);
  }

  *pcounter = num;

  // Semaphore:
  int semid = psemget(IPC_PRIVATE, 2, 0600 | IPC_CREAT | IPC_EXCL);
  psem_up(semid, (*pcounter) % 2);

  for (int i = 0; i < N_PROC; i++) {
    pid_t pid = pfork();

    if (pid == 0) {
      // child
      while (true) {
        psem_down(semid, i);
        if (*pcounter <= 1) {
          psem_up(semid, (*pcounter + 1) % 2);
          exit(EXIT_SUCCESS);
        } else {
          (*pcounter)--;
          printf("Child %d: %d\n", getpid(), *pcounter);
          usleep(500000);
        }

        psem_up(semid, (*pcounter) % 2);
      }
    } else {
      // parent
    }
  }
  for (int i = 0; i < N_PROC; i++) {
    pwait(NULL);
  }
  // destroy sems:
  psemctl(semid, 0, IPC_RMID, NULL);

  // detach shm from pointer address:
  pshmdt(pcounter);
  // destroy shm:
  pshmctl(shmid, IPC_RMID, NULL);
}
