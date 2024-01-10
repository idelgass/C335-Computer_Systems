#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void* uppercase(){
	char c;
        for(int i = 0; i < 10; i++){
                c = rand() % ('Z' + 1 - 'A') + 'A';
                fprintf(stdout, "%c\n", c);
        }
        return NULL;
}
void* lowercase(){
        char c;
        for(int i = 0; i < 10; i++){
                c = rand() % ('z' + 1 - 'a') + 'a';
                fprintf(stdout, "%c\n", c);
        }
        return NULL;
}

int main(int argc, char** argv){
        if(argc != 2){
                fprintf(stderr, "Incorrect number of arguemnts\n");
                exit(1);
        }
	if(!strcmp(*(argv + 1), "-U")) uppercase();
	else if(!strcmp(*(argv + 1), "-l")) lowercase();
	else{
		fprintf(stderr, "Invalid cmd line argument\n");
		exit(1);
	}
	
        return 0;
}

