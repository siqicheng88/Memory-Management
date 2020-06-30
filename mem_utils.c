#include <stdio.h>
#include <assert.h>
#include "mem_impl.h"

#define HEADER_SIZE 24

// Check for possible problems with the free list data structure

freeList* head;

void check_heap() {
  freeList* curr = head->next;
  while (curr && curr->next) {
    // Blocks are ordered with strictly increasing memory addresses
    assert(curr < curr->next);

    // Block sizes are positive number
    assert(curr->size > 0);
    // Size is no smaller than whatever minimum size
    assert(curr->size >= MIN_SIZE);

    // Blocks do not overlap
    // the start + length of a block is not an address in the
    // middle of a later block on the list
    assert((uintptr_t) curr + HEADER_SIZE  + curr->size / 16 * 16 <=
(uintptr_t) curr->next);

    // Blocks are not touching
    /*assert((uintptr_t) curr + HEADER_SIZE  + curr->size / 16 * 16 !=
      (uintptr_t) curr->next);*/
    curr = curr->next;
  }

  // now hit the last block
  if (curr) {
    assert(curr->size > 0);
    assert(curr->size >= MIN_SIZE);
  }
}
