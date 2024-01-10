#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char** argv){
        if(argc != 2){
                fprintf(stderr, "Incorrect number of arguments. Expected 2, Received %d\n", argc);
                exit(1);
        }

        int fd[2];
        if(pipe(fd) == -1){
		fprintf(stderr, "pipe failure\n");
		exit(1);
	}
	
	int frk = fork();
	if(frk == -1){
		fprintf(stderr, "Fork failed\n");
		exit(1);
	}
	else if(frk == 0){
	//Child
		
        	char out[256];

        	int readcd = read(fd[0], out, sizeof(out));
        	out[readcd] = '\0';
        	fprintf(stdout, "%s\n", out);
		close(fd[0]);
	}
	else if(frk > 0){
	//Parent			
        	write(fd[1], *(argv + 1), 256);
        	close(fd[1]);
	}	

        return 0;
}

