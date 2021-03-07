#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>  // file control options
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
    int np;
    char msg[1024];
    switch(id){
        case -1: perror("fork"); exit(1);
        case 0:;   // Child
            if(mkfifo("/tmp/np", 0666) < 0)
                perror("mkfifo");
            while((np = open("/tmp/np", O_RDWR)) < 0){
                ;   // synchronization
            }
            read(np, msg, 1024);    // waits ... 
            strcat(msg, " Systems");
            printf("%s \n", msg);
            write(np, " Systems", 1 + strlen(" Systems"));
            close(np);
            break;
        default:;       // Parent 
            char receivedMessage[1024];
            strcpy(msg, "Operating");
            if(mkfifo("/tmp/np", 0666) < 0){
                perror("mkfifo");
            }
            while((np = open("/tmp/np", O_RDWR)) < 0){
                ; // Synchronization
            }
            printf("Sending message ...\n");
            write(np, msg, (1+ strlen("Operating")));

            int* stat_loc;
            wait(stat_loc);    // Waits for the child process to end

            
            read(np, receivedMessage, 1024);
            strcat(msg, receivedMessage);
            printf("%s \n", msg);

            close(np);
            break;
    }

    return 0;
} 