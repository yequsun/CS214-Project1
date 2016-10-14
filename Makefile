mymalloc: mymalloc.o memgrind.o
	gcc -o mymalloc mymalloc.o memgrind.o

mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c

memgrind.o: memgrind.c mymalloc.h
	gcc -c memgrind.c

clean:
	$(RM) mymalloc memgrind.o mymalloc.o
