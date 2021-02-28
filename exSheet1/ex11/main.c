#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void alineaA(int argc, char* argv[], char* envp[]){
    char* f1 = argv[1];
    char* f2 = argv[2];

    int fileDescriptor1, fileDescriptor2;

    // Get the data read from f1
    void* dataToBeRead = malloc(100);       // Allocate 100 bytes in memory

    fileDescriptor1 = open(f1, O_RDONLY);   // read only
    fileDescriptor2 = open(f2, O_WRONLY);   // write only

    int bytesRead;

    if(fileDescriptor1 == -1 || fileDescriptor2 == -1){
        printf("Files failed to open\n");
        return;
    } else{
        printf("%s and %s are now opened\n", f1, f2);

        while(1){
            bytesRead = read(fileDescriptor1, dataToBeRead, 100);

            if(bytesRead == 0){
                break;
            }

            printf("file content: %s / Bytes read: %d\n", (char*) dataToBeRead, bytesRead);

            write(fileDescriptor2, dataToBeRead, bytesRead);
        }

        close(fileDescriptor1);
        close(fileDescriptor2);
    }
}

void alineaB(int argc, char* argv[], char* envp[]){
    char* f1 = argv[1];
    char* f2 = argv[2];

    // Declare the file pointer
    FILE *filePointer1, *filePointer2;

    // Get the data to be read
    char dataToBeRead[100];

    filePointer1 = fopen(f1, "r");
    filePointer2 = fopen(f2, "w");

    if(filePointer1 == NULL || filePointer2 == NULL){
        printf("Error opening file\n");
    } else {
        printf("The file is now open\n");

        while( fgets(dataToBeRead, 100, filePointer1) != NULL ){
            fputs(dataToBeRead, filePointer2);
        }

        fclose(filePointer1);
        fclose(filePointer2);
    }
}

void alineaC(int argc, char* argv[], char* envp[]){
    char* f1 = argv[1];

    if(argc == 2){
        printf("You only gave us 1 filename: %s\n", f1);
        return;
    }

    char* f2 = argv[2];
    // Declare the file pointer
    FILE *filePointer1, *filePointer2;

    // Get the data to be read
    char dataToBeRead[100];

    filePointer1 = fopen(f1, "r");
    filePointer2 = fopen(f2, "w");

    if(filePointer1 == NULL || filePointer2 == NULL){
        printf("Error opening file\n");
    } else {
        printf("The file is now open\n");

        while( fgets(dataToBeRead, 100, filePointer1) != NULL ){
            fputs(dataToBeRead, filePointer2);
        }

        fclose(filePointer1);
        fclose(filePointer2);
    }

}


int main(int argc, char* argv[], char* envp[]){
    //alineaA(argc, argv, envp);
    //alineaB(argc, argv, envp);
    alineaC(argc, argv, envp);
    return 0;
}
