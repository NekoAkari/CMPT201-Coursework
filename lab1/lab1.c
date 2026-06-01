#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // printf("Please enter some text: \n");

  char *buff = NULL;
  size_t size = 0;

  while (1) {
    printf("Please enter some text: \n");

    ssize_t num_char = getline(&buff, &size, stdin);

    if (num_char == -1) {
      perror("getline falied");
      free(buff);
      exit(EXIT_FAILURE);
    }

    if (num_char == 1) {
      break;
    }

    printf("Tokens: \n");

    char *saveptr = NULL;
    char *token = strtok_r(buff, " \n", &saveptr);
    while (token != NULL) {
      printf(" %s \n", token);
      token = strtok_r(NULL, " \n", &saveptr);
    }
  }
  free(buff);

  return 0;
}
