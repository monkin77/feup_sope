# include <stdio.h> 
# include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void alineaA(int argc, char* argv[], char* envp[]){
    char* fileName = argv[1];

    // Declare the file pointer 
    int fileDescriptor;

    // Get the data to be written in file 
    void* dataToBeRead = malloc(100);

    //open existing file using fopen() in read mode using 'r' attribute
    //fileDescriptor = fopen(fileName, "r");
    fileDescriptor = open(fileName, O_RDONLY);

    if(fileDescriptor == -1){
        printf("%s failed to open!\n", fileName);
    }
    else{
        printf("%s is now opened\n", fileName);
        
        /*
        while( read(fileDescriptor, dataToBeRead, 10) ){    //Read operation is not working properly
            printf("%s", (char*) dataToBeRead);
        };  */
        

        // Closing the file using fclose()
        close(fileDescriptor);
    }
}

void alineaB(int argc, char* argv[], char* envp[]){
    char* fileName = argv[1];

    // Declare the file pointer 
    int fileDescriptor;

    // Get the data to be written in file 
    void* dataToBeRead;

    //open existing file using fopen() in read mode using 'r' attribute
    //fileDescriptor = fopen(fileName, "r");
    fileDescriptor = open(fileName, O_RDONLY);

    if(fileDescriptor == -1){
        fprintf(stderr, "%s failed to open!\n", fileName);
    }
    else{
        printf("%s is now opened\n", fileName);
        
        /*
        while( read(fileDescriptor, dataToBeRead, 10) ){    //Read operation is not working properly
            printf("%s", (char*) dataToBeRead);
        };  */
        

        // Closing the file using fclose()
        close(fileDescriptor);
    }
}

void alineaC(int argc, char* argv[], char* envp[]){
    char* fileName = argv[1];

    // Declare the file pointer 
    int fileDescriptor;

    // Get the data to be written in file 
    void* dataToBeRead;

    //open existing file using fopen() in read mode using 'r' attribute
    //fileDescriptor = fopen(fileName, "r");
    fileDescriptor = open(fileName, O_RDONLY);

    if(fileDescriptor == -1){
        perror("Error:");
    }
    else{
        printf("%s is now opened\n", fileName);
        
        /*
        while( read(fileDescriptor, dataToBeRead, 10) ){    //Read operation is not working properly
            printf("%s", (char*) dataToBeRead);
        };  */
        

        // Closing the file using fclose()
        close(fileDescriptor);
    }
}

int main(int argc, char* argv[], char* envp[]){
    alineaA(argc, argv, envp);

    //alineaB(argc, argv, envp);        Using "2>" we re-direct the error output to a file named "errorfile". ( ./main file2.txt 2> errorfile )

    //alineaC(argc, argv, envp);

    return 0;
}
