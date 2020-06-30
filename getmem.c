#include "mem.h"

#define BS 16384  // the default size of adding new chunk
#define SS 40  // the size bound of spliting a block

freeList* getBlock(uintptr_t size);
freeList* splitBlock(uintptr_t size, freeList* list);
freeList* addBlock(uintptr_t size);
uintptr_t totalSize;
freeList* head;  // record the head of implicit list
freeList* iter;
// record the block location when calling getBlock, used for extra 1
uintptr_t add;  // record the new added chunk's ending address

// get memory from implicit list, return a block of memory with a given size
void* getmem(uintptr_t size) {
  if (size <= 0) {
    return NULL;
  }

  // initialize the head and all other variables
  if (head == NULL) {
    head = (freeList*) malloc(sizeof(freeList) + 8);
    if (head == NULL) {
      return NULL;
    }
    head->next = NULL;
    head->size = 0;
    uintptr_t foot = 0;
    memcpy((void*) ((uintptr_t) head + sizeof(freeList)), &foot, sizeof(foot));
    totalSize = 0;  // set the boundary tag
    add = (uintptr_t) head + sizeof(freeList);
    iter = head;
  }

  check_heap();

  uintptr_t msize = ((size - 1) / 16 + 1) * 16;  // make size|16
  freeList* block = getBlock(msize);
  if (block == NULL) {  //  get a larger added chunk
    uintptr_t getSize = (msize > BS) ? msize : BS;
    block = addBlock(getSize);
    if (block == NULL) {
      return NULL;
    }
    block = getBlock(msize);
  }

  check_heap();
  return (void*) ((uintptr_t)block + sizeof(freeList));
}

// return a large new allocated chunk to the implicit list
freeList* addBlock(uintptr_t size) {
  freeList* block = (freeList*) malloc(sizeof(freeList) + size + 16);
  block->size = add + 3;
  // set the beginning tag of the chunk, make it connected to the previous chunk
  // if a tag % 8 = 1, it is a allocated block, =3, the starter of a block,
  // =0, a free block
  add = (uintptr_t) block + sizeof(freeList) + size + 8;
  block = (freeList*) ((uintptr_t) block + 8);
  block->size = size;
  totalSize += size;
  uintptr_t foot = size;
  memcpy((void*) ((uintptr_t) block + sizeof(freeList) + size),
&foot, sizeof(foot));
  freeList* temp = head;
// make the chunks in increasing order
  if ((uintptr_t) block < (uintptr_t)(temp)) {
    block->next = temp;
    temp = block;
    return block;
  } else {
    while (temp->next != NULL) {
      if ((uintptr_t) block < (uintptr_t)(temp->next)) {
        block->next = temp->next;
        temp->next = block;
        return block;
      }
        temp = temp->next;
    }
  }
  temp->next = block;
  return block;
}

// return a block with given size from the implicit list
freeList* getBlock(uintptr_t size) {
  freeList* tempnode = NULL;
  if (head->next == NULL) {return tempnode;}
  freeList* temp = iter;
  do {
    if (temp->next == NULL) {
      temp = head;
    } else {
      // found block large enough
    if (temp->next->size >= size && temp->next->size % 8 == 0) {
      // splitable
      if (temp->next->size > size + SS) { iter = temp;
        return splitBlock(size, temp->next);
      } else {  // take the whole chunk
        tempnode = temp->next;
        tempnode->size++;
        uintptr_t foot = tempnode->size;
        memcpy((void*) ((uintptr_t) tempnode + sizeof(freeList) +
tempnode->size - 1), &foot, sizeof(foot));
        iter = temp;
        return tempnode;
      }
    } else {
      temp = temp->next;
    }
    }
  } while (temp != iter);
  return tempnode;
}

// split the block, return the needed block of given size
freeList* splitBlock(uintptr_t size, freeList* curr) {
  uintptr_t addr = (uintptr_t)curr + curr->size - size;
  curr->size = curr->size - size - sizeof(freeList) - 8;
  uintptr_t foot = curr->size;
  memcpy((void*) ((uintptr_t) curr + sizeof(freeList) + curr->size),
&foot, sizeof(foot));
  freeList *newBlock = (void*) addr;
  newBlock->size = size + 1;
  newBlock->next = curr->next;
  curr->next = newBlock;
  foot = size + 1;
  memcpy((void*) ((uintptr_t) newBlock + sizeof(freeList) + size),
&foot, sizeof(foot));
  return newBlock;
}
