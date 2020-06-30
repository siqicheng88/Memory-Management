# CSE 374 Homework 6 : Memory Management
- Siqi Cheng
- Kai Gong

## Division Of Work

This project is mainly divided as:
- mem.h (Kai)
- getmem.c (Kai)
- freemem.c (Siqi)
- get_mem_stats.c (Kai)
- print_heap.c (Siqi)
- mem_utils.c (Kai)
- mem_impl.h (Siqi)
- bench.c (Kai)
- Makefile (Siqi)


## Organization And Algorithms Used In The Free List

Our basic version of this project is under tag version1 in gitlab.
The getmem and freemem functions share a single data structure.
Our free list data structure is a linked-list of free memory blocks. Each list has a size field 
containing the size of data it can hold and a pointer to the next node in the linked list.

When the user requests for memory, the list of available memory blocks will be scaned through. 
getmem() will look through free list and find a large enough block to return. If the block is large enough to splite, 
then splite it into two. If there does not exist a block to fit the given size, 
we would add a large new chunk to the free list and search again.

When freemem() is called, our program will called check_heap() to check for possible 
problems with the free list data structure. Then the program will determine 
if the given block needs to be concatenated with the adjacent blocks or not.
If the blocks are adjacent in their physical memory address, we will merge blocks of memory.
If no concatenation needs to be done, the block is just inserted into the list at that location.

## Extra Credit

Responsiblility: Kai
For Extra1, we put the project under the tag hw6-extra1 in gitlab.
It will slightly improve the effiency of the program by avoiding searching through the large amont of little fragments of free space at the beginning of the list every time.
For Extra2, we put it under the tag hw6-extra2 in gitlab.
In this part, we build an implicit list, keep the 'free list' with all the nodes, and just mark them free or allocated. This ruduce the free function into constant time.

## Summary Of Benchmarking
We started our test with 10000 trials and CPU TIME is generally around 0 seconds,which can
be ignore. When we run 1 million operations, CPU TIME is around 2 seconds. Thus, this program is efficient. It will result in around 400 free blocks after 10000 tirals and an average of 4000 bytes per block.

## Summary of Resources

Most of the resources we used for this assignment is from StackOverFlow, Ed discussion board and Google.

