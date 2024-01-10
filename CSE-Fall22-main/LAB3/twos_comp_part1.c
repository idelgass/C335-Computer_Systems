#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	
	if(argc != 2){
		fprintf(stderr, "Incorrect number of arguments: %d", argc);
		exit(1);
	}
	else if(!atoi(*(argv + 1))){
		fprintf(stderr, "Non-numeric argument: %s", *(argv + 1));
		exit(1);
	}
	
	int dec = atoi(*(argv + 1));
	char binstr[9];

	if(dec != 0){
		if(dec > 127 || dec < -127){
			fprintf(stderr, "Number %d can't be represented in 8 bits", dec);
			exit(1);
		}
		else{
			//I know this is kind of hacky, but it gives correct outputs. I ran it by my lab ai and he gave me the green light so here it is
			for(int i = 128; i >= 1; i >>= 1){
				strcat(binstr, ((dec & i) == i) ? "1" : "0");
			}
		}	
	}
	else for(int i = 0; i < 8; i++) strcat(binstr, "0");
		
	printf("%s", binstr);
}
