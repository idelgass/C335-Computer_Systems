#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char** argv){
	if(argc != 3){
		fprintf(stderr, "Incorrect number of arguments given. Expected 3, Received %d\n", argc);
		exit(1);
	}
	char* path = (char*)malloc(256*sizeof(char));
	strcpy(path, "/bin/");
	strcat(path, argv[1]);

	if(execl(path, argv[1], argv[2], NULL) == -1){
		fprintf(stderr, "execl failure\n");
		exit(1);
	}
	
	free(path);
	return 0;
}
