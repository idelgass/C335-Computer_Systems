#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<ctype.h>

#define BIAS 127
#define BINLEN 32
#define EXPLEN 8

//Converts a single decimal value (int or fraction) to a binary string
char* ntobin(double dec, int binlen, bool isfrac);
//Use to check if a non numeric input is given
bool isnumeric(char* str);

int main(int argc, char* argv[]){
	
	double dec; //Holds input float, will be used to store mantissa after normalization
	int exp = 0;
	int sign = 0;
	
	char* manstr, expstr; //Hold mantissa and exponent bin strings respectively
	char binstr[BINLEN + 1];
	
	//Guard conditions
	if(argc != 2){
		fprintf(stderr, "Incorrect number of arguments: %d", argc);
		exit(1);
	}
	if(!isnumeric(argv[1])){
		fprintf(stderr, "Non numeric input given");
		exit(1);
	}
	
	dec = atof(argv[1]);
	
	//Store sign separately and take abs value of dec for normalizaiton
	if(dec >= 0) sign = 1;
	else sign = -1;
	dec *= sign; //Abs value	

	//Normalize dec before converting to binary
        while(dec >= 2){
                dec /= 2;
                exp++;
        }
	while(dec < 1 && dec > 0){
		dec *= 2;
		exp--;
	}
	if(dec > 1) dec--; //Remember the 1 is implicit
	else if(dec){
		fprintf(stderr, "Error normalizing decimal value");
		exit(1);
	}

	//Handle sign bit
	if(sign == 1) strcpy(binstr, "0");
	else if(sign == -1) strcpy(binstr, "1");
	else{
		fprintf(stderr, "Unexpected error: sign not 1 or -1");
		exit(1);
	}
	
	//Handle exp
	strcat(binstr, ntobin((double)(exp + BIAS), EXPLEN, false));
	
	//Handle mantissa
	strcat(binstr, ntobin(dec, BINLEN - EXPLEN - 1, true));	
	printf("%s", binstr);
}

char* ntobin(double dec, int binlen, bool isfrac){
	
	char* bin = (char*)malloc((binlen + 1) * sizeof(char));
	for(int dig = binlen - 1; dig >= 0; dig--){
		bin[binlen] = '\0';
		if(!isfrac){
			if(dec - pow(2, dig) >= 0) {
				dec -= pow(2, dig);
				bin[binlen - 1 - dig] = '1';
			}
			else bin[binlen - 1 - dig] = '0';
		}
		else{
			if(dec - pow(2, -1 * (binlen - dig)) >= 0) {
                                dec -= pow(2, -1 * (binlen - dig));
                                bin[binlen - 1 - dig] = '1';
                        }
                        else bin[binlen - 1 - dig] = '0';

		}
	}
	return bin;
	
}

bool isnumeric(char* str){
	bool decimalFound = false;
	if(*str == '-') return isnumeric(str + 1);

	while(*str) {
		if(*str == '.') {
			if(decimalFound) return false;
			else decimalFound = true;
		}	
		else if(isdigit(*str) == 0) return false;
		str++;
	}

	return true;
}
