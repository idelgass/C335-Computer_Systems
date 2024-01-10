
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int global;

int main(int argc, char** argv){
	if(argc != 2){
		fprintf(stderr, "Incorrect number of arguments. Expected: 2, Received %d\n", argc);
		exit(1);
	}
	
	//Need to implement a guard here
	global = atoi(*(argv + 1));
	
	int frk = fork();
	fprintf(stdout, "Hello World\n");
	if(frk == -1){
		fprintf(stderr, "Fork failed\n");
		exit(1);
	}
	else if(frk == 0){
	//Child
		fprintf(stdout, "Child: %d\n", --global);
		return 0;
	}
	else{
		fprintf(stdout, "Parent %d\n", ++global);
		return 0;
	}
}
