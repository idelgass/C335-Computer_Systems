#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#ifndef ASIZE
	#define ASIZE = 2
#endif

int main(int argc, char* argv[]){
	if(argc != 2){
		fprintf(stderr, "Incorrect number of arguments\n");
		exit(1);
	}	

	int array[ASIZE];
	for (int i = 0; i < ASIZE; i++) {
	   array[i] = i*atoi(argv[1]);
	}
	
	//Partition
	int top[ASIZE/2];
	int bot[ASIZE/2 + ASIZE%2];
	for(int i = 0; i < ASIZE/2; i++) top[i] = array[i];
	for(int i = 0; i < ASIZE/2 + ASIZE%2; i++) bot[i] = array[ASIZE/2 + ASIZE%2 + i];
	
	//Pipe setup
	int fd[2];
	if(pipe(fd) == -1){
		fprintf(stderr, "Pipe failure\n");
		exit(1);
	}
int sum, topsum, botsum = 0;
	int frk = fork();
        if(frk == -1){
                fprintf(stderr, "Fork failed\n");
                exit(1);
        }	
        else if(frk == 0){
	//Child
		for(int i = 0; i < ASIZE/2; i++) topsum += top[i];
                write(fd[1], &topsum, 256);
	       	close(fd[1]);	
		return 0;
        }
        else{
                for(int i = 0; i < ASIZE/2 + ASIZE%2; i++) botsum += bot[i];
		read(fd[0], &topsum, sizeof(topsum));
        	close(fd[0]);
		sum = topsum + botsum;
        	printf("%d\n", sum);
        }
}
