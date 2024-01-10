#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define BIAS 127
#define BINLEN 32
#define EXPLEN 8

float binton(char* binstr, int binlen, bool isfrac);

int main(int argc, char* argv[]){
	//Four values to output
	char signchar;
	int sign;
	int exp;
	float mantissa;
	float number;
	bool normalized = false;

	char bin[BINLEN + 1]; //Will store input string, +1 for null terminator
	char expstr[EXPLEN + 1]; //Will store exponent string 

	//Guard conditions
	if(argc != 2){
		fprintf(stderr, "Incorrect number of arguments");
		exit(1);
	}
	if(strlen(*(argv + 1)) != BINLEN){
		fprintf(stderr, "Incorrect length for bin numner");
		exit(1);
	}

	strcpy(bin, *(argv + 1));
	
	//Handle sign bit
	signchar = bin[0];
	sign = (signchar - '0') ? -1 : 1; //To convert ascii char directly to int rather than casting based on index, subtract char '0'
	
	//Handle the exp (biasing happens in calculation of number)
	strncpy(expstr, bin + 1, 8); //Take substr from index 1 to 9
	exp = binton(expstr, EXPLEN, false);
	if (exp != 0) normalized = true;

	//Handle the mantissa
	mantissa = binton(bin + 9, BINLEN - EXPLEN - 1, true); 
	if (normalized) mantissa += 1; //Adding 1 to normalize
	
	//Calculate number
	number = normalized ? sign * mantissa * pow(2, exp - BIAS) : sign * mantissa * pow(2, 1 - BIAS);

	//Print final output
	printf("Sign: %c\n"
		"Exponent: %d\n"
		"Mantissa: %.17g\n"
		"Number: %.7g\n"
		, signchar, exp, mantissa, number);	
}

float binton(char* binstr, int binlen, bool isfrac){
	float dec = 0;
	int i = 0;
	int dig = binlen - 1; //Reading from left to right, max power length - 1 
	while(dig >= 0){
		//Kind of an ugly oneliner but if the bit is turned on add the appropriate power of two, depending on before or after the decimal
		if(binstr[i] == '1') dec = isfrac ? dec + pow(2, (i + 1) * -1) : dec + pow(2, dig);
		else if(binstr[i] != '0'){
		       fprintf(stderr, "Not a binary numnber");
		       exit(1);
		}
		i++;
		dig--;
	}
	return dec;
}
