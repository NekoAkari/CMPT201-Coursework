#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define PATH "tmp_sock"

int main() {
  // socket();
  int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }
  // bind()
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, PATH, sizeof(addr.sun_path) - 1);
  if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  // listen()
  if (listen(sock_fd, 10) == -1) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // accept()
  int recv_fd = accept(sock_fd, NULL, NULL);
  if (recv_fd == -1) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  // read()
  char buf[1024];
  int size_read = read(recv_fd, buf, sizeof(buf));
  if (size_read > 0) {
    if (write(STDOUT_FILENO, buf, size_read) == -1) {
      perror("write");
      exit(EXIT_FAILURE);
    }
  }

  // close
  close(recv_fd);
  close(sock_fd);
  return 0;
}
