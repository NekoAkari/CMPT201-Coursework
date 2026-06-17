#include <pthread.h>
#include <stdio.h>

#define MAX 1000000

int cnt = 0;

void *count_thread(void *arg) {
  for (int i = 0; i < MAX; i++) {
    cnt++;
  }
  return NULL;
}

int main() {
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, count_thread, NULL);
  pthread_create(&thread2, NULL, count_thread, NULL);

  // Wait for both threads to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Final count: %d\n", cnt);
  printf("Done in main thread.\n");
  return 0;
}
