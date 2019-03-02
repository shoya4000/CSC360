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

void* producer (void* v) {
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // TODO
    uthread_mutex_lock(v);
    if (items < MAX_ITEMS) {
      items++;
    } else {
      producer_wait_count++;
    }
    histogram[items]++;
    uthread_mutex_unlock(v);
  }
  return NULL;
}

void* consumer (void* v) {
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // TODO
    uthread_mutex_lock(v);
    if (items > 0) {
      items--;
    } else {
      consumer_wait_count++;
    }
    histogram[items]++;
    uthread_mutex_unlock(lock);
  }
  return NULL;
}

int main (int argc, char** argv) {
  uthread_t t[4];

  uthread_init (4);

  // TODO: Create Threads and Join
  uthread_mutex_t mt;
  t[0] = uthread_create(producer, (void *)mt);
  t[1] = uthread_create(consumer, (void *)mt);
  t[2] = uthread_create(producer, (void *)mt);
  t[3] = uthread_create(consumer, (void *)mt);
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