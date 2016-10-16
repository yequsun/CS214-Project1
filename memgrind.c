#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "mymalloc.h"

double workloadA(){
	void* p_array[3000];
	int i;
	
	struct timeval t1, t2;
	
	gettimeofday(&t1, NULL);
	
	for(i = 0; i < 3000; i++){
		p_array[i] = malloc(2);
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
	
	for(i = 0; i < 100; i++){
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
				free(p_array[entry]);
				p_array[entry] = p_array[size-1];
				p_array[size-1] = 0;
			}size--;
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
			int blocksize = (rand() % 2500) + 1;
			p_array[size] = malloc(blocksize);
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

double workloadE(){
	void* p_array[150];
	int malloc_count = 0,
	size = 0,
	i;

	struct timeval t1, t2;
	
	gettimeofday(&t1, NULL);

	for(i = 0; i < 150; i++){
		//allocate between 1-16 bytes
		int rannum = (rand() % 15) + 1;
		p_array[malloc_count] = malloc(rannum);
		size++;
		malloc_count++;
	}
	
	while(malloc_count < 3000){

		for(i = 0; i < 50; i++){
			int entry = rand() % size;
			
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

		for(i = 0; i < 50; i++){
			int rannum = (rand() % 15) + 1;
			p_array[size] = malloc(rannum);
			malloc_count++;
			size++;
		}
	}
	
	gettimeofday(&t2, NULL);
	
	double timespent = (t2.tv_sec - t1.tv_sec) * 1000.0;
	timespent += (t2.tv_usec - t1.tv_usec) / 1000.0;
	
	return timespent;
}

double workloadF(){
	void* p_array[150];
	int malloc_count = 0,
	size = 0,
	i;

	struct timeval t1, t2;
	
	gettimeofday(&t1, NULL);


	for(i = 0; i < 150; i++){
		p_array[i] = malloc(1);
		size++;
		malloc_count++;
	}
	
	while(malloc_count < 3000){

		for(i = 0; i < 50; i++){
			int entry = rand() % size;
			
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

		for(i = 0; i < 50; i++){
			p_array[size] = malloc(1);
			malloc_count++;
			size++;
		}
	}

	gettimeofday(&t2, NULL);
	
	double timespent = (t2.tv_sec - t1.tv_sec) * 1000.0;
	timespent += (t2.tv_usec - t1.tv_usec) / 1000.0;

	return timespent;
	
}

void main(){
	
	//srand((unsigned int)time(NULL));
	
	int i;
	double sumA = 0,
		sumB = 0,
		sumC = 0,
		sumD = 0,
		sumE = 0,
		sumF = 0;

	for(i = 0; i < 2; i++){
	init();
	sumA += workloadA();
	//sumB += workloadB();

	//init();
	//sumC += workloadC();
	//init();
	//sumD += workloadD();
	
	//sumE += workloadE();
	//sumF += workloadF();
	}
	print_stats();
	//printf("Workload A averaged %lf ms.\n", (sumA / 100));
	//printf("Workload B averaged %lf ms.\n", (sumB / 100));
	//printf("Workload C averaged %lf ms.\n", (sumC / 100));
	//printf("Workload D averaged %lf ms.\n", (sumD / 100));
	
	//printf("Workload E averaged %lf ms.\n", (sumE / 100));
	//printf("Workload F averaged %lf ms.\n", (sumF / 100));
}
