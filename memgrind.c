#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

void main(){
	
	srand((unsigned int)time(NULL));
	
	//workload A
	char* p_array[3000];
	int i;
	
	for(i = 0; i < 3000; i++){
		p_array[i] = (char *)mymalloc(sizeof(char));
	}
	
	for(i = 0; i < 3000; i++){
		free(p_array[i]);
	}
	
	//workload B
	
	for(i = 0; i < 3000; i++){
		char* ptr = (char *)mymalloc(sizeof(char));
		myfree(ptr);
	}
	
	//workload C
	memset(p_array, 0, sizeof(char *)*3000);
	
	int malloc_counter = 0,
		top = -1;
		rannum;
	
	while(malloc_counter < 3000){
		rannum = rand() % 2;
		
		if(rannum == 0){
			top++;
			p_array[top] = (char *)mymalloc(sizeof(char));
			malloc_counter++;
		}
		else if(rannum == 1 && top >= 0){
			rannum = rand() % (top + 1);
			
			if(rannum == top){
				myfree(p_array[top]);
				p_array[top] = 0;
			}
			else{
				myfree(p_array[rannum]);
				p_array[rannum] = p_array[top];
				p_array[top] = 0;
			}
		}
	}
	
	//workload D
}