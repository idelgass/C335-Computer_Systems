#include<time.h>
#include<stdio.h>

#ifndef SZ
        #define SZ 10
#endif

int A[SZ][SZ];

int main(){
	clock_t begin = clock();
        for(int i = 0; i < SZ; i++){
                for(int j = 0; j < SZ; j++){
                        A[i][j] = i*j;
                }
        }

        for(int j = 0; j < SZ; j++){
                for(int i = 1; i < SZ; i++){
                        A[i][j] = ( A[i][j-1] + A[i][j] ) / 2;
                }
        }
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time taken w size %d: %lf\n", SZ, time_spent);
}

