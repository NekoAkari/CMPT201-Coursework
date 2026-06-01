#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }

    if (line[0] == '\0') {
      break;
    }

    if (strcmp(line, "exit") == 0) {
      break;
    }

    if (strcmp(line, "joke") == 0) {
      printf("Why do programmers prefer dark mode?\nBecause light attracts bugs.");
      continue;
    }

    pid_t pid = fork();

    if (pid == -1) {
      perror("fork");
      continue;
    }

    if (pid == 0) {
      execl(line, line, (char *)NULL);
      printf("Exec failure\n");
      exit(1);
    }

    waitpid(pid, NULL, 0);
  }

  free(line);
  return 0;
}
