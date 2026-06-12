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

void print_data(char *format, char *data, size_t data_size) {
  write(STDOUT_FILENO, format, strlen(format));

  for (size_t i = 0; i < data_size; i++) {
    char buf[BUF_SIZE];
    ssize_t len = snprintf(buf, BUF_SIZE, "%d ", data[i]);

    if (len < 0) {
      handle_error("snprintf");
    }

    write(STDOUT_FILENO, buf, len);
  }
  write(STDOUT_FILENO, "\n", 1);
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

  char *first_data = (char *)first_block_pointer + sizeof(struct header);
  char *second_data = (char *)second_block_pointer + sizeof(struct header);

  size_t data_size = BLOCK_SIZE - sizeof(struct header);

  memset(first_data, 0, data_size);
  memset(second_data, 1, data_size);
  print_out("first block:        %p\n", &first_block_pointer, sizeof(first_block_pointer));
  print_out("second block:       %p\n", &second_block_pointer, sizeof(second_block_pointer));

  print_out("first block size:   %lu\n", &first_block_pointer->size,
            sizeof(first_block_pointer->size));
  print_out("first block next:   %p\n", &first_block_pointer->next,
            sizeof(first_block_pointer->next));

  print_out("second block size:  %lu\n", &second_block_pointer->size,
            sizeof(second_block_pointer->size));
  print_out("second block next:  %p\n", &second_block_pointer->next,
            sizeof(second_block_pointer->next));

  // Print out each byte
  print_data("first block data:   ", first_data, data_size);
  print_data("second block data:  ", second_data, data_size);

  return 0;
}
