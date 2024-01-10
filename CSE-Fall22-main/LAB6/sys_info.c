#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char** argv){
        if(argc != 3){
                fprintf(stderr, "Incorrect number of arguments. Expected 3, Received %d\n", argc);
                exit(1);
        }

        int fd[2];
	//Note this line creates pipe as well as checking it for failure
        if(pipe(fd)){
		fprintf(stderr, "Pipe failure\n");
		exit(1);
	}

        int frk = fork();
        if(frk == -1){
                fprintf(stderr, "Fork failed\n");
                exit(1);
        }
        else if(frk == 0){
        //Child

                char cmd[256];
		char arg[256];
		char path[256];

		//Read from pipe here
		read(fd[0], cmd, sizeof(cmd));
		read(fd[0], arg, sizeof(arg));	
		
		//Set path for command
		char* substr = (char*)malloc(6 * sizeof(char));
		strncpy(substr, cmd, 5);
	       	if(strcmp(substr, "/bin/")){
			strcpy(substr, "/bin/");
			strcat(substr, cmd);
			strcpy(path, substr);
		}
		else if(strcmp(substr, "/bin/") == 0){
			strcpy(path, cmd);
			strncpy(cmd, cmd + 5, 255);
		}
		free(substr);	
		
		//Note this lines runs exec as well as checking it for failure
		if(execl(path, cmd, arg, NULL) == -1){
			fprintf(stderr, "execl failure\n");
			exit(1);
		}
                
                close(fd[0]);
        }
        else if(frk > 0){
        //Parent                        
                write(fd[1], *(argv + 1), 256);
		write(fd[1], *(argv + 2), 256);
                close(fd[1]);
		wait(&frk);
        }


        return 0;
}
