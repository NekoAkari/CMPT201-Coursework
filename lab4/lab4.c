#define _DEFAULT_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HEAP_SIZE 256
#define BLOCK_SIZE 128
#define BUF_SIZE 1024

struct header {
  uint64_t size;
  struct header *next;
};

void initialize_block(struct header *block, struct header *next) {
  block->size = BLOCK_SIZE;
  block->next = next;
}

int main(void) {
  void *start = sbrk(HEAP_SIZE);

  if (start == (void *)-1) {
    perror("sbrk");
    return 1;
  }

  struct header *first_block_pointer = (struct header *)start;
  struct header *second_block_pointer = (struct header *)((char *)start + BLOCK_SIZE);

  initialize_block(first_block_pointer, NULL);
  initialize_block(second_block_pointer, first_block_pointer);

  return 0;
}

void handle_error(char *msg) {
  perror(msg);
  exit(1);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}
