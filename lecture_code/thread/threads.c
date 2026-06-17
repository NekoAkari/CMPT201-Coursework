#define _GNU_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int len = 0;

void *my_func(void *msg) {
  char *new_msg = (char *)msg;
  len = strlen(new_msg);
  printf("Message is: %s\n", new_msg);
  printf("Thread ID is: %d\n", gettid());
  // long long len = strlen(new_msg);
  return (void *)&len;
}

int main() {
  void *result;
  pthread_t mythread;
  pthread_create(&mythread, NULL, my_func, "Hello from main thread.");
  pthread_join(mythread, &result);
  // long long size = (long long)result;
  int size = *(int *)result;
  printf("Main: the return value is: %d\n", size);
  return 0;
}
