#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread.h"

static int counter;
static int THREADS = 2;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t is_even = PTHREAD_COND_INITIALIZER;
static pthread_cond_t is_odd = PTHREAD_COND_INITIALIZER;

struct threadArgs {
  int id;
};

void *thread_main(void *args) {

  // retrieve items from struct
  threadArgs *targs = (threadArgs *)args;
  int id = targs->id;

  while (true) {
    mutex_lock(&mtx);

    if (id % 2 == 0) {
      while (counter % 2 != 0) {
        cond_wait(&is_even, &mtx);
      }
    } else {
      while (counter % 2 == 0) {
        cond_wait(&is_odd, &mtx);
      }
    }

    counter--;

    printf("Child %u: %d\n", (int)pthread_self(), counter);
    usleep(500000);

    if (id % 2 == 0) {
      cond_broadcast(&is_odd);
    } else {
      cond_broadcast(&is_even);
    }

    if (counter == 2 || counter == 1) {
      mutex_unlock(&mtx);
      break;
    }

    mutex_unlock(&mtx);
  }
  return NULL;
}

int main(void) {
  printf("Enter value [10:20]: ");
  scanf("%d", &counter);

  if (counter < 10 || counter > 20) {
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

  mutex_destroy(&mtx);
  cond_destroy(&is_even);
  cond_destroy(&is_odd);
}
