#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>

#define BUFF_SIZE 5

char buff[BUFF_SIZE];
int cursor = 0;
sem_t full, empty, mutex;

void* shift_buff(){
        for(int i = 0; i < BUFF_SIZE - 1; i++) buff[i] = buff[i + 1];
	return NULL;
}

void* uppercase(void* arg){
        char c;
	int id = *(int*)arg;
        
	for(int i = 0; i < BUFF_SIZE; i++){ 
		sem_wait(&empty);
		sem_wait(&mutex);
		c = rand() % ('Z' + 1 - 'A') + 'A';
		buff[cursor++] = c; 
		fprintf(stdout, "writer ID: %d, char written: %c\n", id, c); 
		sem_post(&mutex);
		sem_post(&full);
	}

        return NULL;
}
void* lowercase(void* arg){
        char c;
	int id = *(int*)arg;

	for(int i = 0; i < BUFF_SIZE; i++){
                sem_wait(&empty);
        	sem_wait(&mutex);
		c = rand() % ('z' + 1 - 'a') + 'a';
               	buff[cursor++] = c;
                fprintf(stdout, "writer ID: %d, char written: %c\n", id, c);
		sem_post(&mutex);
        	sem_post(&full);	
	}
        return NULL;
}
void* read_buff(void* arg){
	char c; 
	int id = *(int*)arg;

	for(int i = 0; i < BUFF_SIZE; i++){
		sem_wait(&full);
		sem_wait(&mutex);
		cursor--;
		c = *buff;
		shift_buff();
		fprintf(stdout, "reader ID: %d, char read: %c\n", id, c);
		sem_post(&mutex);
		sem_post(&empty);
	}

	return NULL;
}

int main(int argc, char** argv){
        if(argc != 1){
                fprintf(stderr, "Incorrect number of arguemnts\n");
                exit(1);
        }
	
	srand(time(0));

	if(sem_init(&full, 1, 0) == -1){
		fprintf(stderr, "Semaphore initializaiton failed\n");
		exit(1);
	}
	if(sem_init(&empty, 1, BUFF_SIZE) == -1){
                fprintf(stderr, "Semaphore initializaiton failed\n");
                exit(1);
        }
	if(sem_init(&mutex, 1, 1) == -1){
                fprintf(stderr, "Semaphore initializaiton failed\n");
                exit(1);
        }


	pthread_t tid_w0, tid_w1, tid_w2, tid_w3;
	pthread_t tid_r0, tid_r1, tid_r2, tid_r3;
	
	int id_w0 = 0, id_w1 = 1, id_w2 = 2, id_w3 = 3;
	int id_r0 = 0, id_r1 = 1, id_r2 = 2, id_r3 = 3;

	pthread_create(&tid_w0, NULL, lowercase, (void*)&id_w0);
    	pthread_create(&tid_w1, NULL, lowercase, (void*)&id_w1);
	pthread_create(&tid_w2, NULL, uppercase, (void*)&id_w2);
	pthread_create(&tid_w3, NULL, uppercase, (void*)&id_w3);

	pthread_create(&tid_r0, NULL, read_buff, (void*)&id_r0);
	pthread_create(&tid_r1, NULL, read_buff, (void*)&id_r1);
	pthread_create(&tid_r2, NULL, read_buff, (void*)&id_r2);
	pthread_create(&tid_r3, NULL, read_buff, (void*)&id_r3);

	
	pthread_join(tid_w0, NULL);
        pthread_join(tid_w1, NULL);
        pthread_join(tid_w2, NULL);
        pthread_join(tid_w3, NULL);

        pthread_join(tid_r0, NULL);
        pthread_join(tid_r1, NULL);
        pthread_join(tid_r2, NULL);
        pthread_join(tid_r3, NULL);

	(void)argv[0];

        return 0;
}

