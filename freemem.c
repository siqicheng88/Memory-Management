#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include "mem_impl.h"
#define HEADER_SIZE 16  // the size of freeList*


void freemem(void* p) {
// if p is null, then return immdiately
  if (p == NULL) {
    return;
  }
  check_heap();
  // get the address of block that needs to free
  freeList* toRemove = (freeList*) (p - sizeof(freeList));
  toRemove->size--;
  uintptr_t foot = toRemove->size;
  memcpy((void*) ((uintptr_t) toRemove + sizeof(freeList) + foot),
&foot, sizeof(foot));
  uintptr_t front = (uintptr_t) toRemove - 8;
  uintptr_t* getn = (uintptr_t*) front;
  freeList* curr;
  // combine the previous block if need
  if (*getn % 8 == 0) {
    curr = (freeList*) (front - *getn - 16);
    curr->size = curr->size + curr->next->size + sizeof(freeList) + 8;
    uintptr_t foot = curr->size;
    memcpy((void*) ((uintptr_t) curr + sizeof(freeList) + foot),
&foot, sizeof(foot));
    if (iter == curr->next) {iter = curr;}
      curr->next = curr->next->next;
  } else {curr = toRemove;}
  // combine the later block if need
  uintptr_t back = (uintptr_t) curr + curr->size + 24;
  if (back == (uintptr_t) curr->next) {
    getn = (uintptr_t*) back;
    if (*getn % 8 == 0) {
      curr->size = curr->size + curr->next->size + sizeof(freeList) + 8;
      uintptr_t foot = curr->size;
      memcpy((void*) ((uintptr_t) curr + sizeof(freeList) + foot),
&foot, sizeof(foot));
      if (iter == curr->next) {iter = curr;}
        curr->next = curr->next->next;
    }
  }
  check_heap();
}

