#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv){
	if(argc != 3){
		fprintf(stderr, "Incorrect number of arguments: %d", argc);
		exit(1);
	}
	if(strlen(*(argv + 1)) != 8){
		fprintf(stderr, "Number is not 8 bits");
	}
	int dec = 0;
	char dig;

	if(!strcmp("unsigned", *(argv + 2))){
		//Unsigned code
		//Iterating over binary string from msb to lsb
		for(int i = 0; i < strlen(*(argv + 1)); i++){
			dig = *(*(argv + 1) + i);
			if(dig == '1'){
				dec += 1<<(7 - i); //8 bits so max power is 7, left shift by x = multiply by 2^x
			}
			else if(dig != '0'){
				fprintf(stderr, "Illegal character in binary string: %c", dig);
				exit(1);
			}
		}	
	}
	else if(!strcmp("signed", *(argv + 2))){
		//Signed code
		//Initial for loop is basically the same as unsigned, just ignoring the sign bit.
		//Could I condense these and reduce reduncancy while simplifying my code? Yes.
		for(int i = 1; i < strlen(*(argv + 1)); i++){
			dig = *(*(argv + 1) + i);
			if(dig == '1'){
				dec += 1<<(7 - i);
			}
			else if(dig != '0'){
				fprintf(stderr, "Illegal character in binary string: %c", dig);
				exit(1);
			}
		}
		if(**(argv + 1) == '1') dec -= 128; // To convert from twos complement for n bit number subtract off sign bit * 2^(n - 1) 
	}

	printf("%d", dec);
}
