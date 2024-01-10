#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>

sem_t sem;

void* thread_routine_A(){
        if(sem_wait(&sem) == -1){
		fprintf(stderr, "Semaphore decrement failed\n");
		exit(1);
	}
	printf("A\n");
	return NULL;
}
void* thread_routine_B(){
        if(sem_wait(&sem) == -1){
                fprintf(stderr, "Semaphore decrement failed\n");
                exit(1);
        }
        printf("B\n");
        return NULL; 
}
void* thread_routine_C(){
        // FIX for code issue
	sem_post(&sem);

	if(sem_wait(&sem) == -1){
                fprintf(stderr, "Semaphore decrement failed\n");
                exit(1);
        }
        printf("C\n");
        return NULL;
}


int main(int argc, char** argv){
	if(argc != 1){
		fprintf(stderr, "Incorrect number of arguments\n");
		exit(1);
	}

        if(sem_init(&sem, 1, 2) == -1){
                fprintf(stderr, "Semaphore initialization failed\n");
                exit(1);
        }

        pthread_t tid_A, tid_B, tid_C;
        if(pthread_create(&tid_A, NULL, thread_routine_A, NULL)){
                fprintf(stderr, "Pthread creation failed\n");
                exit(1);
        }
	if(pthread_create(&tid_B, NULL, thread_routine_B, NULL)){
                fprintf(stderr, "Pthread creation failed\n");
                exit(1);
        }
	if(pthread_create(&tid_C, NULL, thread_routine_C, NULL)){
                fprintf(stderr, "Pthread creation failed\n");
                exit(1);
        }

        if(pthread_join(tid_A, NULL) == -1){
                fprintf(stderr, "Pthread join failed\n");
                exit(1);
        }
	if(pthread_join(tid_B, NULL) == -1){
                fprintf(stderr, "Pthread join failed\n");
                exit(1);
        }
	if(pthread_join(tid_C, NULL) == -1){
                fprintf(stderr, "Pthread join failed\n");
                exit(1);
        }

	(void)argv[0];

        return 0;
}
