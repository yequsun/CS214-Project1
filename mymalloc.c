#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

max_size = sizeof(myblock);
min_alloc = 1;
Metadata* first_metadata = &myblock[0]

void init(){
	Metadata* initial_metadata = first_metadata;
	initial_metadata->size = max_size - sizeof(Metadata);
	initial_metadata->alloc_flag = 0;
	initial_metadata->prev_index = 0;
	initial_metadata->last_flag = 1;
}


Metadata* next(Metadata* cur){
	//return the metadata pointer of the next block	
	//check last flag before calling this method
	char* ret;
	ret = (char*)cur;
	ret += sizeof(Metadata);
	ret += cur->size;
	return (Metadata*)ret;
}

Metadata* prev(Metadata* cur){
	//return the metadata pointer of the previous block
	char* ret;
	ret = (char*)myblock[cur->prev_index];
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
	ret += sizeof(Metadata);
	return (void*)ret;
}

int get_index(Metadata* cur){
	char* a = &myblock[0];
    char* b = &myblock[1];
    int offset = b - a;
    //calculate the offset between 2 neighboring indexes
	int ret;
	ret = (cur - first_metadata)/offset;
	return ret;
}

void* mymalloc(size_t req_size,const char* file_name, int line_number){

	/*if(req_size<=0 || req_size>5000){
		printf("Error\n");
		exit(0);
	}

	char* cur = &myblock[0];
	while(cur <= &myblock[5000]){
		if(!allocated(cur) && actual_size(cur)<= req_size){
			int size_before = actual_size(cur);
			*(int*)cur = set_metadata(req_size,1);
			int size_remains = size_before - actual_size(cur);
			*(int*)(cur+4+actual_size(cur)) = set_metadata(size_remains,0);
			return (cur+4);
		}else{
			cur = cur + 4 + actual_size(cur);
		}
	}
	*/
	if(req_size + sizeof(Metadata) > max_size){
		return null;
		//no enough space
	}

	if(req_size<min_alloc){
		req_size = min_alloc;
		//the minimal allocated size is 8 bytes
	}

	Metadata* cur = &myblock[0];//Start from the first metadata
	do{
		if(!allocated(cur) && get_size(cur)>=req_size){
			//this block fits. Allocate memory here
			int old_size = get_size(cur);
			int old_last_flag = cur->last_flag;
			cur->alloc_flag = 1;

			if( (get_size(cur)-req_size) >= (sizeof(Metadata)+min_alloc) ){//if the space left is enough for one block
				cur->size = req_size;
				Metadata* new_metadata;
				char* temp = (char*)cur;
				temp += (sizeof(Metadata)+get_size(cur));
				new_metadata = (Metadata*)temp;

				new_metadata->alloc_flag = 0;
				new_metadata->size = old_size-sizeof(Metadata);
				new_metadata->last_flag = old_last_flag;
				new_metadata->prev_index = get_index(new_metadata);
			}

			return get_address(cur);
		}else if(is_last(cur)){
			//This is the last block but no match
			return NULL;
		}else{
			//go to next blcok
			cur = next(cur);
		}
	}while(!is_last(cur));
	return NULL;
}
