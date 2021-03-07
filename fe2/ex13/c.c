#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

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
    char msg[1024];
    switch(id){
        case -1: perror("fork"); exit(1);
        case 0:;   // Child
            //close(pp[1]);   // closes the writing end of the File (File descriptor)
            read(pp[0], msg, 1024);     // waits for message to appear in the file ...
            strcat(msg, " Systems");    // concatenates the 2nd argument into the first
            printf("%s \n",msg);
            close(pp[0]);   // closes the reading end of the File (File descriptor)
            write(pp[1], " Systems", 1 + strlen(" Systems"));
            close(pp[1]);
            break;
        default:       // Parent
            strcpy(msg, "Operating");
            char receivedMsg[1024];    
            //close(pp[0]);   // closes the reading end of the File (File descriptor)
            printf("Sending message ...\n");
            write(pp[1], msg, 1+strlen("Operating"));
            close(pp[1]);   // closes the writing end of the File (File descriptor)

            int* stat_loc;
            wait(stat_loc);    // Waits for the child process to end

            read(pp[0], receivedMsg, 1024);
            strcat(msg, receivedMsg);
            printf("%s \n", msg);   
            close(pp[0]);
            break;
    }

    return 0;
} 