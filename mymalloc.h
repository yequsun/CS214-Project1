#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

#include <stdlib.h>

static char myblock[5000];
//memory block

Metadata* first_metadata;
//pointer to the head of the metadata list

const int max_size;
//the capacity of the block
const int min_alloc;
//minimum allocated size

int get_index(Metadata* cur);

void* get_address(Metadata* cur);

typedef struct{
	unsigned int size:31;//The size of this block
	unsigned int alloc_flag:1;//If the block is allocated. 0 - not. 1 - yes
	unsigned int prev_index:31;//The index number in myblock[] of the previous block metadata
	unsigned int last_flag:1;//If this block is the last block. 0- not. 1 -yes
}Metadata;

Metadata* prev(Metadata* cur); //returns the pointer to the previous block.

Metadata* next(Metadata* cur); //returns the pointer to the next block.

void init();


void* mymalloc(size_t size, const char* file_name, int line_number);

void myfree(void* ptr, const char* file_name, int line_number);

#endif
