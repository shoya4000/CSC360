#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"
#include "spinlock.h"

#define MAX_ITEMS 10
const int NUM_ITERATIONS = 200;
const int NUM_CONSUMERS  = 2;
const int NUM_PRODUCERS  = 2;

int producer_wait_count;     // # of times producer had to wait
int consumer_wait_count;     // # of times consumer had to wait
int histogram [MAX_ITEMS + 1]; // histogram [i] == # of times list stored i items

int items = 0;

struct thread_start_arg {
  uthread_mutex_t lock;
  uthread_cond_t produce;
  uthread_cond_t consume;
};

void* producer (void* v) {
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // TODO
    uthread_mutex_lock(v->lock);
    while (items == MAX_ITEMS) {
      producer_wait_count++;
      uthread_cond_wait(v->produce);
    }
    items++;
    histogram[items]++;
    uthread_cond_broadcast(v->consume);
    uthread_mutex_unlock(v->lock);
  }
  return NULL;
}

void* consumer (void* v) {
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // TODO
    uthread_mutex_lock(v->lock);
    while (items == MAX_ITEMS) {
      consumer_wait_count++;
      uthread_cond_wait(v->consume);
    }
    items--;
    histogram[items]++;
    uthread_cond_broadcast(v->produce);
    uthread_mutex_unlock(v->lock);
  }
  return NULL;
}

int main (int argc, char** argv) {
  uthread_t t[4];

  uthread_init (4);

  // TODO: Create Threads and Join
  struct thread_start_arg *start_arg = malloc(sizeof(struct thread_start_arg));
  start_arg->lock = uthread_mutex_create();
  start_arg->produce = uthread_cond_create(start_arg->lock);
  start_arg->consume = uthread_cond_create(start_arg->lock);
  t[0] = uthread_create(producer, start_arg);
  t[1] = uthread_create(consumer, start_arg);
  t[2] = uthread_create(producer, start_arg);
  t[3] = uthread_create(consumer, start_arg);
  for (int i = 0; i < 4; i++) {
    uthread_join(t[i], NULL);
  }

  printf ("producer_wait_count=%d\nconsumer_wait_count=%d\n", producer_wait_count, consumer_wait_count);
  printf ("items value histogram:\n");
  int sum = 0;
  for (int i = 0; i <= MAX_ITEMS; i++) {
    printf ("  items=%d, %d times\n", i, histogram [i]);
    sum += histogram [i];
  }
  assert (sum == sizeof (t) / sizeof (uthread_t) * NUM_ITERATIONS);
}