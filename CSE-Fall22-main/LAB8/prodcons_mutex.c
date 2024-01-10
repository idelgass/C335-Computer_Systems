#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

int msg;
sem_t r_mutex, w_mutex;

void* thread_routine(void* arg){
        int n = *(int*)arg;
	for(int i = 0; i < n; i++){
        	if(sem_wait(&r_mutex) == -1){
			fprintf(stderr, "Semaphore decrement failed\n");
			exit(1);
		}
		msg = rand() % (n - 1) + 1;
                fprintf(stdout, "writer wrote: %d\n", msg);
		if(sem_post(&w_mutex) == -1){
			fprintf(stderr, "Semaphore increment failed\n");
			exit(1);
		}
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

	if(sem_init(&r_mutex, 1, 1) == -1){
                fprintf(stderr, "Semaphore initialization failed\n");
                exit(1);
        }
        if(sem_init(&w_mutex, 1, 0) == -1){
                fprintf(stderr, "Semaphore initializaiton failed\n");
                exit(1);
        }

        pthread_t tid;
        if(pthread_create(&tid, NULL, thread_routine, (void*)&n)){
                fprintf(stderr, "Pthread creation failed\n");
                exit(1);
        }
	
        for(int i = 0; i < n; i++){		
		if(sem_wait(&w_mutex) == -1){
			fprintf(stderr, "Semaphore decrement failed\n");
			exit(1);
		}
		fprintf(stdout, "main read: %d\n", msg);
		if(sem_post(&r_mutex) == -1){
			fprintf(stderr, "Semaphore increment failed\n");
			exit(1);
		}	
        }

	if(pthread_join(tid, NULL) == -1){
		fprintf(stderr, "Pthread join failed\n");
		exit(1);
	}

        return 0;
}
