#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "uthread.h"
#include "uthread_sem.h"

#define MAX_ITEMS 10
const int NUM_ITERATIONS = 200;
const int NUM_CONSUMERS  = 2;
const int NUM_PRODUCERS  = 2;

int histogram [MAX_ITEMS + 1]; // histogram [i] == # of times list stored i items

int items = 0;

struct thread_start_arg {
  uthread_sem_t lock;
  uthread_sem_t produce;
  uthread_sem_t consume;
};

void* producer (void* v) {
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // TODO
    struct thread_start_arg *start_arg = (struct thread_start_arg*)v;
    uthread_sem_wait(start_arg->produce);
    uthread_sem_wait(start_arg->lock);
    items++;
    histogram[items]++;
    uthread_sem_signal(start_arg->lock);
    uthread_sem_signal(start_arg->consume);
  }
  return NULL;
}

void* consumer (void* v) {
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // TODO
    struct thread_start_arg *start_arg = (struct thread_start_arg*)v;
    uthread_sem_wait(start_arg->consume);
    uthread_sem_wait(start_arg->lock);
    items--;
    histogram[items]++;
    uthread_sem_signal(start_arg->lock);
    uthread_sem_signal(start_arg->produce);
  }
  return NULL;
}

int main (int argc, char** argv) {
  uthread_t t[4];

  uthread_init (4);

  // TODO: Create Threads and Join
  struct thread_start_arg *start_arg = malloc(sizeof(struct thread_start_arg));
  start_arg->lock = uthread_sem_create(1);
  start_arg->produce = uthread_sem_create(MAX_ITEMS);
  start_arg->consume = uthread_sem_create(0);
  t[0] = uthread_create(&producer, start_arg);
  t[1] = uthread_create(&consumer, start_arg);
  t[2] = uthread_create(&producer, start_arg);
  t[3] = uthread_create(&consumer, start_arg);
  for (int i = 0; i < 4; i++) {
    uthread_join(t[i], NULL);
  }
  uthread_sem_destroy(start_arg->produce);
  uthread_sem_destroy(start_arg->consume);
  uthread_sem_destroy(start_arg->lock);
  free(start_arg);

  printf ("items value histogram:\n");
  int sum = 0;
  for (int i = 0; i <= MAX_ITEMS; i++) {
    printf ("  items=%d, %d times\n", i, histogram [i]);
    sum += histogram [i];
  }
  assert (sum == sizeof (t) / sizeof (uthread_t) * NUM_ITERATIONS);
}