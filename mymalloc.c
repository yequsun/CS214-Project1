#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int max_size = sizeof(myblock);
int min_alloc = 1;
Metadata* first_metadata = (Metadata*)&myblock[0];

void init(){
	memset(myblock,0,sizeof(myblock));
	Metadata* initial_metadata = first_metadata;
	initial_metadata->size = 5000 - sizeof(Metadata);
	initial_metadata->alloc_flag = 0;
	initial_metadata->prev_size = 0;
	initial_metadata->last_flag = 1;
}


Metadata* next(Metadata* cur){
	//return the metadata pointer of the next block	
	//check last flag before calling this method
	char* ret;
	ret = (char*)cur;
	ret += sizeof(Metadata)/sizeof(char);
	ret += cur->size;
	return (Metadata*)ret;
}

Metadata* prev(Metadata* cur){
	//return the metadata pointer of the previous block
	char* ret;
	ret = (char*)cur;
	ret -= cur->prev_size;
	ret -= sizeof(Metadata);
	return (Metadata*)ret;
}

int allocated(Metadata* cur){
	if(cur->alloc_flag){
		return 1;
	}else{
		return 0;
	}
}

int get_size(Metadata* cur){
	return cur->size;
}

int is_last(Metadata* cur){
	return cur->last_flag;
}

void* get_address(Metadata* cur){
	char* ret;
	ret = (char*)cur;
	ret += sizeof(Metadata)/sizeof(char);
	return (void*)ret;
}

/*int get_index(Metadata* cur){
	char* a = &myblock[0];
    char* b = &myblock[1];
    int offset = b - a;
    //calculate the offset between 2 neighboring indexes
	int ret;
	ret = (cur - first_metadata)/offset;
	return ret;
}
*/

void* mymalloc(size_t req_size,const char* file_name, int line_number){

	if(req_size + sizeof(Metadata) > max_size){
		printf("Error in %s, line %d: Not enough space.\n", file_name, line_number);
		return NULL;
	}

	if(req_size<min_alloc){
		req_size = min_alloc;
		//the minimal allocated size is 8 bytes
	}

	Metadata* cur = first_metadata;//Start from the first metadata
	while(!(cur < first_metadata || (char *)cur > &myblock[max_size-1])){
		if(!allocated(cur) && get_size(cur)>=req_size){
			//this block fits. Allocate memory here
			int old_size = get_size(cur);
			int old_last_flag = cur->last_flag;
			cur->alloc_flag = 1;

			if( (get_size(cur)-req_size) >= (sizeof(Metadata)+min_alloc) ){//if the space left is enough for one block
				cur->size = req_size;
				Metadata* new_metadata;
				char* temp = (char*)cur;
				temp += (sizeof(Metadata))/sizeof(char);
				temp += get_size(cur);
				new_metadata = (Metadata*)temp;

				//set attributes for new metadata
				new_metadata->alloc_flag = 0;
				new_metadata->size = old_size-sizeof(Metadata)-cur->size;
				new_metadata->last_flag = old_last_flag;
				cur->last_flag = 0;
				new_metadata->prev_size = get_size(cur);
			}
			return get_address(cur);
		}else if(is_last(cur)){
			printf("Error in %s, line %d: No suitable empty space.\n", file_name, line_number);
		
			//This is the last block but no match
			return NULL;
		}else{
			//go to next blcok
			cur = next(cur);
		}
	};
	return NULL;
}

void myfree(void* ptr, const char* file_name, int line_number){

	if(ptr == NULL){
		//printf("Error in %s, line %d: Null pointer.\n", file_name, line_number);
		return;
	}

	Metadata* meta_ptr = (Metadata*)(ptr - sizeof(Metadata));
		
	if(meta_ptr < first_metadata || (char *)ptr > &myblock[max_size-1]){
		printf("Error in %s, line %d: Invalid pointer.\n", file_name, line_number);
		return;
	}
	
	if(!allocated(meta_ptr)){
		printf("Error in %s, line %d: Can't free unallocated memory.\n", file_name, line_number);
		return;
	}
	
	meta_ptr->alloc_flag = 0;
	int new_size;
	
	//merge right
	Metadata* nxt = next(meta_ptr);
	if(meta_ptr->last_flag == 0 && nxt->alloc_flag == 0){
		new_size = get_size(meta_ptr) + get_size(nxt) + sizeof(Metadata);
		meta_ptr->size = new_size;
	}
			
	//merge left
	Metadata* prv = prev(meta_ptr);
	if(meta_ptr!= first_metadata && prv->alloc_flag == 0){
		new_size = get_size(meta_ptr) + get_size(prv) + sizeof(Metadata);
		prv->size = new_size;
	}
}

void print_stats(){
	Metadata* cur = first_metadata;
	int blocks = 0;
	int allocated_blocks = 0;
	int unallocated_blocks = 0;
	int allocated_space = 0;
	int unallocated_space = 0;

	while(1){
		blocks++;
		if(allocated(cur)){
			allocated_blocks++;
			allocated_space += get_size(cur);
		}else{
			unallocated_blocks++;
			unallocated_space += get_size(cur);
		}

		if(is_last(cur)){
			break;
		}
		cur = next(cur);
	}
	printf("No. of blocks: %d, No. of allocated blocks:%d, No. of unallocated blocks:%d, allocated_space: %d, unallocated space: %d\n",blocks,allocated_blocks,unallocated_blocks,allocated_space,unallocated_space);
}
