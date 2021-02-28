#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void alineaA(int argc, char *argv[], char *envp[])
{
    char *directoryPath = argv[1];

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
        if (S_ISDIR(inode.st_mode))
            printf("dir ");
        else if (S_ISREG(inode.st_mode))
            printf("fis ");
        else if (S_ISLNK(inode.st_mode))
            printf("lnk ");
        else
            ;
        printf(" %s\n", dirEntry->d_name);
    }
}

void alineaB(int argc, char *argv[], char *envp[])
{
    char *directoryPath = argv[1];

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
    int noRegFiles = 0;

    while ((dirEntry = readdir(dirPointer)) != 0){
        sprintf(name, "%s/%s", directoryPath, dirEntry->d_name); // sends formatted output to a string(name) / name will be the absolute path to the next file
        lstat(name, &inode);                                     // get info about the file/folder at the path name

        // test the type of file
        if (S_ISDIR(inode.st_mode))
            printf("dir ");
        else if (S_ISREG(inode.st_mode)){
            printf("fis ");
            noRegFiles++;
        }
        else if (S_ISLNK(inode.st_mode)){
            printf("lnk ");
            noRegFiles++;
        }
        printf(" %s\n", dirEntry->d_name);
    }

    printf("No. regular files: %d\n", noRegFiles);

}

int main(int argc, char *argv[], char *envp[])
{
    //alineaA(argc, argv, envp);
    alineaB(argc, argv, envp);
    return 0;
}
