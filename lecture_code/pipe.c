#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int pipefd[2], pipefd2[2];
  char buf;
  pid_t cpid;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (cpid == 0) {    /* Child reads from pipe */
    close(pipefd[1]); /* Close unused write end */
    close(pipefd2[0]);

    while (read(pipefd[0], &buf, 1) > 0) {
      buf = (char)toupper(buf);
      write(STDOUT_FILENO, &buf, 1);
    }
    write(pipefd2[1], "\n", 1);
    close(pipefd[0]);
    close(pipefd2[1]);
    _exit(EXIT_SUCCESS);

  } else {            /* Parent writes argv[1] to pipe */
    close(pipefd[0]); /* Close unused read end */
    close(pipefd2[1]);
    write(pipefd[1], argv[1], strlen(argv[1]));
    close(pipefd[1]); /* Reader will see EOF */
    while (read(pipefd2[0], &buf))
      wait(NULL); /* Wait for child */
    exit(EXIT_SUCCESS);
  }
}
