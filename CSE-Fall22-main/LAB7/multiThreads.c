#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
//#include<time.h>

typedef struct s_thread_args{
	int id;
	char path[256];
	char word[256];
} threadArgs;

int wordCount(FILE* fp, char* word){
        char line[256];
        char* wordp;
        int cursor, wordc = 0;
        while((fgets(line, sizeof(line), fp)) != NULL){
                cursor = 0;
                while((wordp = strstr(line + cursor, word)) != NULL){
                        cursor = wordp - line + 1;
                        wordc++;
                }
        }
        return wordc;
}


void* thread_routine(void* arg){
	//clock_t start = clock();
	threadArgs* targs = (threadArgs*)arg;
        FILE* fp = fopen(targs->path, "r");
        if(!fp){
                fprintf(stderr, "File %s does not exist or cannot be opened\n", targs->path);
                exit(1);
        }
	printf("%s Count: %d\n", targs->word, wordCount(fp, targs->word));
	//clock_t stop = clock();	
	//printf("Time elapsed (%d): %f\n", targs->id, (double)(stop - start)/CLOCKS_PER_SEC);
	return NULL;
}


int main(int argc, char** argv){
	//clock_t start = clock();
	if(argc != 5){
                fprintf(stderr, "Incorrect number of arguments");
                exit(1);
        }

	threadArgs targs_1, targs_2;
	targs_1.id = 1;
	targs_2.id = 2;
	strcpy(targs_1.path, "./");
	strcat(targs_1.path, *(argv + 1));
	strcpy(targs_1.word, *(argv + 2));
	strcpy(targs_2.path, "./");
	strcat(targs_2.path, *(argv + 3));
	strcpy(targs_2.word, *(argv + 4));

	pthread_t tid_1, tid_2;
        if(pthread_create(&tid_1, NULL, thread_routine, (void*)&targs_1)){
		fprintf(stderr, "Pthread creation failed");
		exit(1);
	}
        if(pthread_create(&tid_2, NULL, thread_routine, (void*)&targs_2)){
		fprintf(stderr, "Pthread creation failed");
		exit(1);
	}
        if(pthread_join(tid_1, NULL)){
		fprintf(stderr, "Pthread join failed");
		exit(1):
	}
	if(pthread_join(tid_2, NULL)){
		fprintf(stderr, "Pthread join failed");
		exit(1);
	}
	//clock_t stop = clock();
	//printf("Time elapsed (main): %f\n", (double)(stop - start)/CLOCKS_PER_SEC);
        return 0;
}

