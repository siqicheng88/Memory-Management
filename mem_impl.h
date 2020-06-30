#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#ifndef MEM_IMPL_
#define MEM_IMPL_

#define MIN_SIZE 16

// the free list  structure
typedef struct freeList {
    uintptr_t size;
    struct freeList *next;
} freeList;

// front of the implicit list
extern freeList* head;
// location of the search, used for extra 1
extern freeList* iter;
// location of the end of implicit list
extern uintptr_t add;

extern uintptr_t totalSize;

// Check for bugs with the free list data structure
void check_heap(void);
// check if the two blocks are adjacent, if so merge them
freeList* check_merge(freeList* node);
#endif
