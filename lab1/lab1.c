#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Please enter some text: \n");

  char *buff = NULL;
  size_t size = 0;
  ssize_t num_char = getline(&buff, &size, stdin);

  if (num_char == -1) {
    perror("getline falied");
    free(buff);
    return 1;
  }

  printf("You entered: %s", buff);

  free(buff);

  return 0;
}
