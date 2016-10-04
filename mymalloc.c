#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

void init(){
	*(int*)&myblock[0] = 5000;
}

int allocated(char* metadata_ptr){
	int input = *(int*)&metadata_ptr;
	if(input%2){
		return 0;
	}else{
		return 1;
	}
}

int actual_size(char* metadata_ptr){
	int input = *(int*)&metadata_ptr;
	if(input%2==0){
		//It's unallocated, the value of the int is the actual size.
		return input;
	}else{
		//It's allocated, the value -1 is the actual size.
		return input-1;
	}
}

int set_metadata(size_t req_size,int allocated){
	int allocate_size;
	int metadata;
	if(req_size%2!=0){
		allocate_size+=1;
	}
	metadata = allocate_size + allocated;
	return metadata;
}

void* mymalloc(size_t req_size){

	if(req_size<=0 || req_size>5000){
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
}
