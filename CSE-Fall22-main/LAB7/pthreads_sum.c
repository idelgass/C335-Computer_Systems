#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#ifndef ASIZE
        #define ASIZE = 2
#endif
#ifndef NTHREADS
	#define NTHREADS = 2
#endif

int array[ASIZE];
int sums[NTHREADS];

void* thread_routine(void* arg){
	int id = *(int*)arg; 
	if(id < NTHREADS - 1){
		for(int i = 0; i < ASIZE / NTHREADS; i++){
			sums[id] += *(array + i + id*(ASIZE/NTHREADS)); 
		}
	}
	else{
		for(int i = 0; i < ASIZE / NTHREADS + ASIZE % NTHREADS; i++){
		       sums[id] += *(array + i + id*(ASIZE / NTHREADS + ASIZE % NTHREADS));
		}
	}		
	return NULL;
}

int main(int argc, char* argv[]){
        if(argc != 2){
                fprintf(stderr, "Incorrect number of arguments\n");
                exit(1);
        }

	pthread_t tids[NTHREADS];
	int ids[NTHREADS];
	
	//Partition;
        for(int i = 0; i < ASIZE; i++) {
           array[i] = i*atoi(argv[1]);
        }
	
	for(int i = 0; i < NTHREADS; i++){
		ids[i] = i;
		if(pthread_create(&tids[i], NULL, thread_routine, (void*)&ids[i]) == -1){
			fprintf(stderr, "Pthread creation failed");
			exit(1);
		}
	}
	int sum = 0;
	for(int i = 0; i < NTHREADS; i++){
	       	sum += sums[i];
		if(pthread_join(tids[i], NULL)){
				fprintf(stderr, "Pthread join failed");
				exit(1);
		}
	}
	printf("%d\n", sum);
}

