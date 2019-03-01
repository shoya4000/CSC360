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

spinlock_t lock;

void* producer (void* v) {
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // TODO
    if (items < MAX_ITEMS) {
      spinlock_lock(&lock);
      items++;
      histogram[items]++;
      spinlock_unlock(&lock);

    }
  }
  return NULL;
}

void* consumer (void* v) {
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // TODO
    if (items > 0) {
      spinlock_lock(&lock);
      items--;
      histogram[items]++;
      spinlock_unlock(&lock);

    }
  }
  return NULL;
}

int main (int argc, char** argv) {
  uthread_t t[4];

  uthread_init (4);

  // TODO: Create Threads and Join
  spinlock_create(&lock);
  t[0] = uthread_create(producer, &items);
  t[1] = uthread_create(consumer, &items);
  t[2] = uthread_create(producer, &items);
  t[3] = uthread_create(consumer, &items);
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
  printf("sum: %d\n", sum);
  printf("sizeof (t): %lu\n", sizeof (t));
  printf("sizeof (uthread_t): %lu\n", sizeof (uthread_t));
  printf("NUM_ITERATIONS: %d\n", NUM_ITERATIONS);
  printf("sizeof (t) / sizeof (uthread_t) * NUM_ITERATIONS: %lu", (sizeof (t) / sizeof (uthread_t) * NUM_ITERATIONS));
  assert (sum == sizeof (t) / sizeof (uthread_t) * NUM_ITERATIONS);
}