#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>

void func(int signo) {
	//printf("I'm here\n");
    ;
}

void readDirectoryRecursive(char* directoryPath, int indent){
    // opens a directory. Returns a valid pointer if the successfully, NULL otherwise
    DIR *dirPointer = opendir(directoryPath);

    if (dirPointer == NULL)
    {
        printf("Error opening directory\n");
        return;
    }

    struct dirent *dirEntry;
    struct stat inode;
    char name[1000];

    while ((dirEntry = readdir(dirPointer)) != 0)
    {
        sprintf(name, "%s/%s", directoryPath, dirEntry->d_name); // sends formatted output to a string(name) / name will be the absolute path to the next file
        lstat(name, &inode);                                     // get info about the file/folder at the path name

        // test the type of file
        if (S_ISDIR(inode.st_mode)){
            if(strcmp(dirEntry->d_name, ".") == 0 || strcmp(dirEntry->d_name, "..") == 0)
                continue;
            int pid = fork();

            struct sigaction new, old;
            sigset_t smask;	// defines signals to block while func() is running

            // prepare struct sigaction
            if (sigemptyset(&smask)==-1)	// block no signal
                perror ("sigsetfunctions");
            new.sa_handler = func;  // function that will be called with the new signal
            new.sa_mask = smask;
            new.sa_flags = 0;	// usually works
            
            switch(pid){
                case 0:
                    if(sigaction(SIGUSR1, &new, &old) == -1)	// Sigaction system call changes the action taken by a process upon receipt of a specific signal
                        perror ("sigaction");
                    pause();    // wait for signal from parent
                    readDirectoryRecursive(name, indent+2);
                    exit(0);        // need to end the child process here, since otherwise it would print the files that are already being printed by the parent
                    break;
                default:
                    printf("%*c", indent, ' ');
                    printf("%s %s\n", "dir ", dirEntry->d_name);
                    usleep(10000);
                    //sleep(1);   // use a sleep here to ensure the child is ready to receive the signal
                    kill(pid, SIGUSR1);
                    int* stat_loc;
                    wait(stat_loc);    // Waits for the child process to end
                    break;
            }
        }
        else if (S_ISREG(inode.st_mode)){
            printf("%*c", indent, ' ');
            printf("fis ");
            printf(" %s\n", dirEntry->d_name);
        }
        else if (S_ISLNK(inode.st_mode)){
            printf("%*c", indent, ' ');
            printf("lnk ");
            printf(" %s\n", dirEntry->d_name);
        }
        else
            ;
    }
    closedir(dirPointer);
    return;
}

int main(int argc, char *argv[], char *envp[])
{
    char *directoryPath = argv[1];

    readDirectoryRecursive(directoryPath, 0);

    return 0;
}
