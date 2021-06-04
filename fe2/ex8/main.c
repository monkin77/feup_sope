#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void func(int signo) {
	fprintf(stderr, "Received signal %d!\n", signo);
}

int main(void){
    struct sigaction new, old;
    sigset_t smask;	// defines signals to block while func() is running

    // prepare struct sigaction
    if (sigemptyset(&smask)==-1)	// block no signal
        perror ("sigsetfunctions");
    new.sa_handler = func;  // function that will be called with the new signal
    new.sa_mask = smask;
    new.sa_flags = 0;	// usually works

    if(sigaction(SIGUSR1, &new, &old) == -1)	// Sigaction system call changes the action taken by a process upon receipt of a specific signal
                perror ("sigaction");

    int id = fork();    // PID of the child process is returned in the parent, and 0 is returned in the child.

    switch(id){
        case -1: perror("fork"); exit(1);
        case 0:                              
            pause();	// wait for the arrival of a signal

            fprintf(stdout, "Hello \n"); 
            break;
        default: 
            sleep(1);       // even though the parent process starts after the child, the child process waits for the parent to send the signal
            fprintf(stdout, "World!\n");
            kill(id, SIGUSR1);      // Sends signal to process of process id = id
            break;
    }

    return 0;
} 