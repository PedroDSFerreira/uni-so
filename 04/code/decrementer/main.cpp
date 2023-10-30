#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread.h"

static int COUNTER;
static int THREADS = 2;
static pthread_mutex_t MTX = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t IS_EVEN = PTHREAD_COND_INITIALIZER;
pthread_cond_t IS_ODD = PTHREAD_COND_INITIALIZER;

struct threadArgs {
  int id;
};

void *thread_main(void *args) {

  // retrieve items from struct
  threadArgs *targs = (threadArgs *)args;
  int id = targs->id;

  while (true) {
    mutex_lock(&MTX);

    if (id % 2 == 0) {
      while (COUNTER % 2 != 0) {
        cond_wait(&IS_EVEN, &MTX);
      }
    } else {
      while (COUNTER % 2 == 0) {
        cond_wait(&IS_ODD, &MTX);
      }
    }

    COUNTER--;

    printf("Child %u: %d\n", (int)pthread_self(), COUNTER);
    usleep(500000);

    if (id % 2 == 0) {
      cond_broadcast(&IS_ODD);
    } else {
      cond_broadcast(&IS_EVEN);
    }

    if (COUNTER == 2 || COUNTER == 1) {
      mutex_unlock(&MTX);
      break;
    }

    mutex_unlock(&MTX);
  }
  return NULL;
}

int main(void) {
  printf("Enter value [10:20]: ");
  scanf("%d", &COUNTER);

  if (COUNTER < 10 || COUNTER > 20) {
    printf("Invalid value\n");
    exit(EXIT_FAILURE);
  }

  pthread_t thr[THREADS];
  // Create threads
  for (int i = 0; i < THREADS; i++) {
    threadArgs *args = new threadArgs;
    args->id = i;

    pthread_create(&thr[i], NULL, thread_main, (void *)args);
  }

  // Wait for the threads to finish
  for (int i = 0; i < THREADS; i++) {
    pthread_join(thr[i], NULL);
  }

  mutex_destroy(&MTX);
  cond_destroy(&IS_EVEN);
  cond_destroy(&IS_ODD);
}
