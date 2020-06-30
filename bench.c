#include "mem.h"
#include <string.h>
#include <time.h>
#include <getopt.h>

// exercise the memory management package and report its statistics
int main(int argc, char** argv) {
  clock_t t1 = clock();  // starter time
  uintptr_t total_size = 0;
  uintptr_t total_free = 0;
  uintptr_t n_free_blocks = 0;
  int ntrials = 10000;
  int pctget = 50;
  int pctlarge = 10;
  int small_limit = 200;
  int large_limit = 20000;
  int seed = 1234;
  int opt;
  while ((opt = getopt(argc, argv, "n::g::l::s::b::r::")) != -1) {
    switch (opt) {
      case 'n':
        ntrials = atoi(optarg);
        break;
      case 'g':
        pctget = atoi(optarg);
        break;
      case 'l':
        pctlarge = atoi(optarg);
        break;
      case 's':
        small_limit = atoi(optarg);
        break;
      case 'b':
        large_limit = atoi(optarg);
        break;
      case 'r':
        seed = atoi(optarg);
        break;
      default:
        fprintf(stderr, "Invalid argument passed.\n");
        return EXIT_FAILURE;
    }
  }

  void* getList[ntrials];  // put the gotten memory
  int size = 0;  // count the size of getList
  srand(seed);

  for (int i = 1; i <= ntrials; i++) {
    int j = rand() % 100;
    if (j < pctget) {
      int k = rand() % 100;
      int rbsize;
      if (k < pctlarge) {
        rbsize = (rand() % (large_limit - small_limit)) + small_limit;
      } else {
        rbsize = (rand() % small_limit) + 1;
      }
      getList[size] = getmem(rbsize);  // get a memory with random size
      if (rbsize > 16) {rbsize = 16;}
      memset(getList[size], 0xFE, rbsize);
      size++;
    } else {
      if (size != 0) {
        int index = rand() % size;
        freemem(getList[index]);  // free a random block in the getList
        getList[index] = getList[size - 1];
        size = size - 1;
      }
    }
    if (i % (ntrials / 10) == 0) {
      clock_t t2 = clock();
      double cpu = 1000.0*(t2-t1)/CLOCKS_PER_SEC;
      printf("CPU time: %.2f ms\n", cpu);
      get_mem_stats(&total_size, &total_free, &n_free_blocks);
      printf("total storage accquired: %lu\n", total_size);
      printf("total free blocks: %lu\n", n_free_blocks);
      printf("average bytes per free block: %lu\n", total_free / n_free_blocks);
    }
  }
  return EXIT_SUCCESS;
}
