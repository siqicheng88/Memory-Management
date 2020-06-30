bench: bench.c freemem.c getmem.c get_mem_stats.c print_heap.c mem_utils.c
	gcc -std=c11 -Wall -g -o bench freemem.c getmem.c get_mem_stats.c print_heap.c bench.c mem_utils.c

#individual source file 
print_heap.o: print_heap.c mem_impl.h 
	gcc -Wall -g -std=c11 -c print_heap.c

freemem.o: freemem.c mem_impl.h mem.h
	gcc -Wall -g -std=c11 -c freemem.c

get_mem_stats.o: get_mem_stats.c  mem.h
	gcc -Wall -g -std=c11 -c get_mem_stats.c

mem_utils.o: mem_utils.c mem_impl.h
	gcc -Wall -g -std=c11 -c mem_utils.c

bench.o: bench.c mem.h
	gcc -Wall -g -std=c11 -c bench.c

getmem.o: getmem.c mem_impl.h 
	gcc -Wall -g -std=c11 -c getmem.c

clean:
	rm -rf *.o bench *~

test: bench
	./bench
