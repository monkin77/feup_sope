#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    int id = fork();    // PID of the child process is returned in the parent, and 0 is returned in the child.

    switch(id){
        case -1: perror("fork"); exit(1);
        case 0:                               
            fprintf(stdout, "Hello "); 
            break;
        default: 
            //waitpid(id); 
            fprintf(stdout, "World!\n");
            break;
    }


    return 0;
} 

/*
    For the parent to run first, there is no way to wait for the process to end, since if the parent process ends, then all the children processes
    will end. So the only way for the parent process to run first is by allowing it to run in the standard order, although I am not sure
    if it guarantees that the parent goes first.
*/