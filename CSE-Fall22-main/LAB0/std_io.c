#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if(strcmp(argv[1], "printf") == 0){
		if(argc != 3){
			printf("Incorrect number of arguments\n");
			exit(EXIT_FAILURE);
		}
		printf("You entered: %s\n", argv[2]);
	}
	if(strcmp(argv[1], "fprintf") == 0){
		if(argc != 3){
                        printf("Incorrect number of arguments\n");
                        exit(EXIT_FAILURE);
                }
		FILE *fileptr = fopen("print.txt", "w");
		fprintf(fileptr,"%s", argv[2]);
		fclose(fileptr);
        } 
	if(strcmp(argv[1], "scanf") == 0){
		if(argc != 2){
                        printf("Incorrect number of arguments\n");
                        exit(EXIT_FAILURE);
                }
		char str[101];
		printf("Please enter your input: ");
		scanf("%100s", str);
		printf("You entered: %100s\n", str);
        }
	exit(EXIT_SUCCESS);
}
