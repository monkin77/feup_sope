#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]) {    // Memory test
    while(1){
        system("vmstat -a");
        char* allocatedSpace = (char *) malloc(50*1024*1024);
        
        memset(allocatedSpace, 'A', 50*1024*1024);

        if(allocatedSpace == NULL)
            break;

    
        sleep(1);
    }

    return 0;
}

// https://www.thegeekstuff.com/2012/01/time-command-examples/
// Test with time utility aswell
// /usr/bin/time -f "\nsize: %D ; %K ; %X ; %p (Kilobytes)\npaging: %Z (bytes) ; %F ; %R ; %M ; %t (Kilobytes)\nswap: %W\n" ./main
