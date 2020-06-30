#include <stdint.h>
#include <stdio.h>
#include "mem_impl.h"

#define HEADER_SIZE 16

// print the formatted list on the file to show the blocks on the free list
void print_heap(FILE* f) {
  if (f == NULL) {
    fprintf(stderr, "No such file.\n");
    return;
  } else {
    freeList* node = head;
    while (node) {
      fprintf(f, "Address: %p Length: %lu \n", node, (uintptr_t) node->size);
      node = node->next;
    }
  }
}
