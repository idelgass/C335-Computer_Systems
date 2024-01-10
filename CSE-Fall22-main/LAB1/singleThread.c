#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int WordCount(FILE* fp, char* word);

int main(int argc, char** argv){
	if(argc < 5){
		fprintf(stderr, "Insufficient number of arguments: %d\n", argc);
		exit(1);
	}
	FILE* fp1 = fopen(*(argv + 1), "r");
	if(!fp1){
		fprintf(stderr, "File %s does not exist or cannot be opened\n", *(argv + 1));
		exit(1);
	}
	FILE* fp2 = fopen(*(argv + 3), "r");
	if(!fp2){
		fprintf(stderr, "File %s does not exist or cannot be opened\n", *(argv + 3));
		exit(1);
	}

	printf("The number of times %s appears in %s is %d\n", *(argv + 2), *(argv + 1), WordCount(fp1, *(argv + 2)));	
	printf("The number of times %s appears in %s is %d\n", *(argv + 4), *(argv + 3), WordCount(fp2, *(argv + 4)));
}

int WordCount(FILE* fp, char* word){
		double time;
		clock_t start = clock();
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
		clock_t stop = clock();
		//printf("Time elapsed: %f", (double)(stop - start)/CLOCKS_PER_SEC); 
		return wordc;
				
}
