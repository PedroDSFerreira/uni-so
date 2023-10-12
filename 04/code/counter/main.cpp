#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread.h"

static int COUNTER;

void *thread_main(void *arg) {
  int i;
  printf("Enter value [10:20]: ");
  scanf("%d", &i);

  for (; COUNTER <= i; COUNTER++) {
    printf("Child: %d\n", COUNTER);
    usleep(500000);
  }
  return NULL;
}

int main(void) {
  printf("Enter value [1:9]: ");
  scanf("%d", &COUNTER);

  pthread_t thr;
  thread_create(&thr, NULL, thread_main, NULL);
  thread_join(thr, NULL);

  for (; COUNTER >= 1; COUNTER--) {
    printf("Parent: %d\n", COUNTER);
    usleep(500000);
  }
}
