#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mymalloc.h"

void main(){
	
	srand((unsigned int)time(NULL));
	void* p_array[3000];
	int i;
	
	//workload A
	for(i = 0; i < 3000; i++){
		p_array[i] = mymalloc(1);
	}
	
	for(i = 0; i < 3000; i++){
		free(p_array[i]);
	}
	
	//workload B
	
	for(i = 0; i < 3000; i++){
		void* ptr = mymalloc(1);
		myfree(ptr);
	}
	
	//workload C
	memset(p_array, 0, sizeof(void *)*3000); //clear out the array
	
	int malloc_counter = 0,
		size = 0,
		rannum;
	
	while(malloc_counter < 3000){
		rannum = rand() % 2;
		
		//if rand() chose 0, or if the stack is empty, malloc a new byte
		if(rannum == 0 || size == 0){
			p_array[size] = mymalloc(sizeof(char));
			malloc_counter++;
			size++;
		}
		//otherwise, choose a random entry and free it, then fill in the gap with the top entry
		else{
			int entry = rand() % (size);
			
			if(entry == (size - 1)){
				myfree(p_array[entry]);
				p_array[entry] = 0;
			}
			else{
				myfree(p_array[rannum]);
				p_array[rannum] = p_array[size-1];
				p_array[size-1] = 0;
			}
			size--;
		}
	}
	
	//free any remaining pointers
	while(size > 0){
		myfree(p_array[size-1]);
		size--;
	}
	
	
	//workload D - same as C but with variable sized mallocs
	
	malloc_counter = 0,
	size = 0;
	while(malloc_counter < 100){
		rannum = rand() % 2;
		
		//if rand() chose 0, or if the stack is empty, malloc a new byte
		if(rannum == 0 || size == 0){
			int blocksize = rand() % 2500;
			p_array[size] = mymalloc(blocksize);
			malloc_counter++;
			size++;
		}
		//otherwise, choose a random entry and free it, then fill in the gap with the top entry
		else{
			int entry = rand() % (size);
			
			if(entry == (size - 1)){
				myfree(p_array[entry]);
				p_array[entry] = 0;
			}
			else{
				myfree(p_array[entry]);
				p_array[entry] = p_array[size-1];
				p_array[size-1] = 0;
			}
			size--;
		}
	}
	
	//free any remaining pointers
	while(size > 0){
		myfree(p_array[size-1]);
		size--;
	}
}