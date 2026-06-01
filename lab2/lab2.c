#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter programs to run.\n");
    printf("> ");

    ssize_t read = getline(&line, &len, stdin);

    if (read == -1) {
      break;
    }

    printf("You typed: %s", line);
  }

  free(line);
  return 0;
}
