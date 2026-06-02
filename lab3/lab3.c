#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *line = NULL;
  char *history[5] = {NULL};
  int count = 0;
  size_t len = 0;

  while (1) {
    printf("Enter input: ");

    // Get input
    ssize_t read = getline(&line, &len, stdin);

    if (read == -1) {
      break;
    }

    // Add to history if not reach 5
    if (count < 5) {
      history[count] = strdup(line);
      count++;
    } else { // Remove the oldest record
      free(history[0]);

      for (int i = 0; i < 4; i++) {
        history[i] = history[i + 1];
      }

      history[4] = strdup(line);
    }

    // Print history
    if (strcmp(line, "print\n") == 0) {
      for (int i = 0; i < count; i++) {
        printf("%s", history[i]);
      }
    }
  }

  // Free up all history
  for (int i = 0; i < count; i++) {
    free(history[i]);
  }

  free(line);
  return 0;
}
