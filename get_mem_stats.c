#include "mem.h"

// get information aobut the memory statement
void get_mem_stats(uintptr_t* total_size,
uintptr_t* total_free, uintptr_t* n_free_blocks) {
  *total_size = totalSize;
  uintptr_t totalFree = 0;
  uintptr_t freeBlocks = 0;
  freeList *temp = head->next;
  while (temp != NULL) {
    if (temp->size % 8 == 0) {
      totalFree += temp->size;
      freeBlocks++;
    }
    temp = temp->next;
  }
  *total_free = totalFree;
  *n_free_blocks = freeBlocks;
}
