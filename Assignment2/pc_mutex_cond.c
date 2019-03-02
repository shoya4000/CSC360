#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define MAX_ITEMS 10
const int NUM_ITERATIONS = 200;
const int NUM_CONSUMERS  = 2;
const int NUM_PRODUCERS  = 2;

int producer_wait_count;     // # of times producer had to wait
int consumer_wait_count;     // # of times consumer had to wait
int histogram [MAX_ITEMS + 1]; // histogram [i] == # of times list stored i items

int items = 0;

struct thread_args {
  uthread_mutex_t lock;
  uthread_cond_t can_produce;
  uthread_cond_t can_consume;
};

void* producer (void* v) {
  struct thread_args *args = (struct thread_args*)v;
  uthread_mutex_t lock = args->lock;
  uthread_cond_t can_produce = args->can_produce;
  uthread_cond_t can_consume = args->can_consume;

  for (int i = 0; i < NUM_ITERATIONS; i++) {
    uthread_mutex_lock(lock);

    while (items == MAX_ITEMS) {
      producer_wait_count += 1;
      uthread_cond_wait(can_produce);
    }

    items += 1;
    histogram[items] += 1;
    uthread_cond_broadcast(can_consume);
    uthread_mutex_unlock(lock);
  }
  return NULL;
}

void* consumer (void* v) {
  struct thread_args *args = (struct thread_args*)v;
  uthread_mutex_t lock = args->lock;
  uthread_cond_t can_produce = args->can_produce;
  uthread_cond_t can_consume = args->can_consume;

  for (int i = 0; i < NUM_ITERATIONS; i++) {
    uthread_mutex_lock(lock);

    while (items == 0) {
      consumer_wait_count += 1;
      uthread_cond_wait(can_consume);
    }

    items -= 1;
    histogram[items] += 1;
    uthread_cond_broadcast(can_produce);
    uthread_mutex_unlock(lock);
  }
  return NULL;
}

int main (int argc, char** argv) {
  int THREAD_COUNT = NUM_CONSUMERS + NUM_PRODUCERS;

  uthread_t t[THREAD_COUNT];
  uthread_init (THREAD_COUNT);

  struct thread_args *args = malloc(sizeof(struct thread_args));
  args->lock = uthread_mutex_create();
  args->can_produce = uthread_cond_create(args->lock);
  args->can_consume = uthread_cond_create(args->lock);

  for (int i = 0; i < THREAD_COUNT; i++) {
    if (i % 2 == 0) {
      t[i] = uthread_create(&consumer, args);
    } else {
      t[i] = uthread_create(&producer, args);
    }
  }

  for (int i = 0; i < THREAD_COUNT; i++) {
    uthread_join(t[i], NULL);
  }

  uthread_cond_destroy(args->can_produce);
  uthread_cond_destroy(args->can_consume);
  uthread_mutex_destroy(args->lock);
  free(args);

  printf ("producer_wait_count=%d\nconsumer_wait_count=%d\n", producer_wait_count, consumer_wait_count);
  printf ("items value histogram:\n");
  int sum = 0;
  for (int i = 0; i <= MAX_ITEMS; i++) {
    printf ("  items=%d, %d times\n", i, histogram [i]);
    sum += histogram [i];
  }
  assert (sum == sizeof (t) / sizeof (uthread_t) * NUM_ITERATIONS);
}
