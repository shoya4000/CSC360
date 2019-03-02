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
  volatile spinlock_t *lock = (spinlock_t *) v;

  for (int i = 0; i < NUM_ITERATIONS; i++) {
    spinlock_lock(lock);
    if (items < MAX_ITEMS) {
      items += 1;
    } else {
      producer_wait_count += 1;
    }
    histogram[items] += 1;
    spinlock_unlock(lock);
  }
  return NULL;
}

void* consumer (void* v) {
  volatile spinlock_t *lock = (spinlock_t *) v;

  for (int i = 0; i < NUM_ITERATIONS; i++) {
    spinlock_lock(lock);
    if (items > 0) {
      items -= 1;
    } else {
      consumer_wait_count += 1;
    }
    histogram[items] += 1;
    spinlock_unlock(lock);
  }
  return NULL;
}

int main (int argc, char** argv) {
  int THREAD_COUNT = NUM_CONSUMERS + NUM_PRODUCERS;

  uthread_t t[THREAD_COUNT];
  uthread_init (THREAD_COUNT);

  spinlock_t lock;
  spinlock_create(&lock);

  for (int i = 0; i < THREAD_COUNT; i++) {
    if (i % 2 == 0) {
      t[i] = uthread_create(&consumer, (void *)&lock);
    } else {
      t[i] = uthread_create(&producer, (void *)&lock);
    }
  }

  for (int i = 0; i < THREAD_COUNT; i++) {
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
