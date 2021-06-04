#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void func(int signo) {
	fprintf(stderr, "Received signal %d!\n", signo);
}

int main(void){
    //int proc;
    int pp[2];  // pipe
    if(pipe(pp) == -1){
        perror("Pipe()");
        exit(1);
    }

    int id = fork();    // PID of the child process is returned in the parent, and 0 is returned in the child.

    switch(id){
        case -1: perror("fork"); exit(1);
        case 0:;   // Child
            char *msg = (char *) malloc (1024);
            close(pp[1]);   // closes the writing end of the File (File descriptor)
            read(pp[0], msg, 1024);     // waits for message to appear in the file ...
            strcat(msg, " Systems");    // concatenates the 2nd argument into the first
            printf("%s \n",msg);
            close(pp[0]);   // closes the reading end of the File (File descriptor)
            free(msg);
            break;
        default:       // Parent         
            close(pp[0]);   // closes the reading end of the File (File descriptor)
            printf("Sending message ...\n");
            write(pp[1], "Operating", 1+strlen("Operating"));
            close(pp[1]);   // closes the writing end of the File (File descriptor)
            break;
    }

    return 0;
} 