#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//argv[0] is program name
//argv[1] is file to search thru
//argv[2] is word to search for
int main(int argc, char**  argv){
	//Problem 1
	if(argc < 3){
		fprintf(stderr, "Insufficient arguments\n");
		exit(1);
	}	
	FILE* fp = fopen(*(argv + 1), "r");
	if(fp == NULL){
		fprintf(stderr, "File %s does not exist or cannot be opened\n", *(argv + 1));
		exit(1);
	}
	char line[256];
	int wordc = 0;
	while(fgets(line, sizeof(line), fp)){
		if(strstr(line, *(argv + 2))) wordc++;	
	}	
	printf("The number of times %s appears in %s is %d\n", *(argv + 2), *(argv + 1), wordc);
	fclose(fp);	
}

