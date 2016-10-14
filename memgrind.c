#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
//#include "mymalloc.h"

double workloadA(){
	void* p_array[3000];
	int i;
	
	struct timeval t1, t2;
	
	gettimeofday(&t1, NULL);
	
	for(i = 0; i < 3000; i++){
		p_array[i] = malloc(1);
	}
	
	for(i = 0; i < 3000; i++){
		free(p_array[i]);
	}
	
	gettimeofday(&t2, NULL);
	
	double timespent = (t2.tv_sec - t1.tv_sec) * 1000.0;
	timespent += (t2.tv_usec - t1.tv_usec) / 1000.0;
	
	return timespent;
}

double workloadB(){
	int i;
	
	struct timeval t1, t2;
	
	gettimeofday(&t1, NULL);
	
	for(i = 0; i < 3000; i++){
		void* ptr = malloc(1);
		free(ptr);
	}
	
	gettimeofday(&t2, NULL);
	
	double timespent = (t2.tv_sec - t1.tv_sec) * 1000.0;
	timespent += (t2.tv_usec - t1.tv_usec) / 1000.0;
		
	return timespent;
}

double workloadC(){
	void* p_array[3000];
	
	int malloc_counter = 0,
		size = 0,
		rannum;
	
	struct timeval t1, t2;
	
	gettimeofday(&t1, NULL);
	
	while(malloc_counter < 3000){
		rannum = rand() % 2;
		
		//if rannum is 0 or if the array is empty, malloc a new byte
		if(rannum == 0 || size == 0){
			p_array[size] = malloc(1);
			malloc_counter++;
			size++;
		}
		//otherwise, choose a random entry and free it, then fill in the gap with the top entry
		else{
			int entry = rand() % size;
			
			if(entry == (size - 1)){
				free(p_array[entry]);
				p_array[entry] = 0;
			}
			else{
				free(p_array[rannum]);
				p_array[rannum] = p_array[size-1];
				p_array[size-1] = 0;
			}
			size--;
		}
	}
	
	//free any remaining pointers
	while(size > 0){
		free(p_array[size-1]);
		size--;
	}
	
	gettimeofday(&t2, NULL);
	
	double timespent = (t2.tv_sec - t1.tv_sec) * 1000.0;
	timespent += (t2.tv_usec - t1.tv_usec) / 1000.0;
	
	return timespent;
}

double workloadD(){
	void* p_array[3000];
	
	int malloc_counter = 0,
	size = 0;
	
	struct timeval t1, t2;
	
	gettimeofday(&t1, NULL);
	
	while(malloc_counter < 100){
		int rannum = rand() % 2;
		
		//if rand() chose 0, or if the stack is empty, malloc a new byte
		if(rannum == 0 || size == 0){
			int blocksize = rand() % 2500;
			p_array[size] = malloc(blocksize);
			malloc_counter++;
			size++;
		}
		//otherwise, choose a random entry and free it, then fill in the gap with the top entry
		else{
			int entry = rand() % (size);
			
			if(entry == (size - 1)){
				free(p_array[entry]);
				p_array[entry] = 0;
			}
			else{
				free(p_array[entry]);
				p_array[entry] = p_array[size-1];
				p_array[size-1] = 0;
			}
			size--;
		}
	}
	
	//free any remaining pointers
	while(size > 0){
		free(p_array[size-1]);
		size--;
	}
	
	gettimeofday(&t2, NULL);
	
	double timespent = (t2.tv_sec - t1.tv_sec) * 1000.0;
	timespent += (t2.tv_usec - t1.tv_usec) / 1000.0;
	
	return timespent;
}


void main(){
	
	srand((unsigned int)time(NULL));
	
	workloadA();
	workloadB();
	workloadC();
	workloadD();
	
	//workloadE();
	//workloadF();
}