#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_impl.h"
#ifndef MEM_H
#define MEM_H

// get memory block of size size
void* getmem(uintptr_t size);

// free the memory block stored at pointer p
void freemem(void * p);

// take addresses of total_size, total_free and n_free_blocks,s tore statistics
// about the current state of the memory manager in the three integers
void get_mem_stats(uintptr_t* total_size,
uintptr_t* total_free, uintptr_t* n_free_blocks);

// prints a list of all the blocks on the free list
void print_heap(FILE * f);
#endif
