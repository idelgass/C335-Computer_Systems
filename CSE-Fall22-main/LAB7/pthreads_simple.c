#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

#ifndef INCCNT
#define INCCNT = 0;
#endif


void* thread_routine_1(void* arg){
	char* str = (char*)arg;
	strcat(str, " Example");
      	printf("Concat String: %s\n", str);	
	return NULL;
}

void* thread_routine_2(void* arg){
	int n = *(int*)arg; 
	n += INCCNT;
	printf("Count: %d\n", n);
	return NULL;
}


int main(int argc, char** argv){
	if(argc != 3){
		fprintf(stderr, "Incorrect number of arguments");
		exit(1);
	}
	char cmd_arg_1[256];	
	strcpy(cmd_arg_1, *(argv + 1));
	int  cmd_arg_2;
	cmd_arg_2 = atoi(*(argv + 2));

	pthread_t tid_1, tid_2;
	if(pthread_create(&tid_1, NULL, thread_routine_1, (void*)&cmd_arg_1)){
		fprintf(stderr, "Pthread creation failed");
		exit(1);
	}
	if(pthread_create(&tid_2, NULL, thread_routine_2, (void*)&cmd_arg_2)){
		fprintf(stderr, "Pthread creation failed");
		exit(1);
	}	
	if(pthread_join(tid_1, NULL)){
		fprintf(stderr, "Pthread join failed");
		exit(1);
	}
	if(pthread_join(tid_2, NULL)){
		fprintf(stderr, "Pthread join failed");
		exit(1);
	}
		
	return 0;
}

