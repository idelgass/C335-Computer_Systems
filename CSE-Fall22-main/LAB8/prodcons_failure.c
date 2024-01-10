#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int msg;

void* thread_routine(void* arg){
	int n = *(int*)arg;
	for(int i = 0; i < n; i++){
		msg = rand() % (n - 1) + 1;
		fprintf(stdout, "writer wrote: %d\n", msg);
	}
	return NULL;
}

int main(int argc, char** argv){
	if(argc != 2){
		fprintf(stderr, "Incorrect number of arguemnts\n");
		exit(1);
	}

	int n = atoi(*(argv + 1));
	if(n == 0){
		fprintf(stderr, "Invalid input\n");
		exit(1);
	}

	pthread_t tid;
	if(pthread_create(&tid, NULL, thread_routine, (void*)&n)){
                fprintf(stderr, "Pthread creation failed\n");
                exit(1);
        }

	for(int i = 0; i < n; i++){
		fprintf(stdout, "main read: %d\n", msg);
	}

	if(pthread_join(tid, NULL)){
		fprintf(stderr, "Pthread join failed\n");
		exit(1);
	}
	
       	return 0;	
}
