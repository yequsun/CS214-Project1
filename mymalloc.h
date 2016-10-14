#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

#include <stdlib.h>

static char myblock[5000]; //memory block

typedef struct{
	unsigned int size:31;//The size of this block
	unsigned int alloc_flag:1;//If the block is allocated. 0 - not. 1 - yes
	unsigned int prev_index:31;//The index number in myblock[] of the previous block metadata
	unsigned int last_flag:1;//If this block is the last block. 0- not. 1 -yes
}Metadata;

Metadata* first_metadata;
//pointer to the head of the metadata list

int get_size(Metadata* cur);//size of the block

int get_index(Metadata* cur);//index of the metadata in myblock[]

int is_last(Metadata* cur);//if this block is the last one

void* get_address(Metadata* cur); //pointer to the start of the allocated space

Metadata* prev(Metadata* cur); //returns the pointer to the previous block.

Metadata* next(Metadata* cur); //returns the pointer to the next block.

void init();//initalize the metadata of the first block


void* mymalloc(size_t size, const char* file_name, int line_number);

void myfree(void* ptr, const char* file_name, int line_number);

#endif
