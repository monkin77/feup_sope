#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>  // file control options

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
    switch(id){
        case -1: perror("fork"); exit(1);
        case 0:;   // Child
            char *msg = (char *) malloc (1024);
            if(mkfifo("/tmp/np", 0666) < 0)
                perror("mkfifo");
            while((np = open("/tmp/np", O_RDONLY)) < 0){
                ;   // synchronization
            }
            read(np, msg, 1024);    // waits ... 
            strcat(msg, " Systems");
            printf("%s \n", msg);
            close(np);
            free(msg);
            break;
        default:;       // Parent         
            if(mkfifo("/tmp/np", 0666) < 0){
                perror("mkfifo");
            }
            while((np = open("/tmp/np", O_WRONLY)) < 0){
                ; // Synchronization
            }
            printf("Sending message ...\n");
            write(np, "Operating", (1+ strlen("Operating")));
            close(np);
            break;
    }

    return 0;
} 