#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char buff[15];  // is on stack
    int pass = 0;   // is on stack

    printf("\n Enter the password : \n");

    //gets(buff);
    fgets(buff, 13, stdin); // changed to this
    
    printf("Address of buff[0]: %p address of buff[14]: %p and addr of pass: %p\n", &buff[0], &buff[14], &pass);
    fflush(stdout);

    if (strcmp(buff, "thegeekstuff")) {
        printf("\n Wrong Password. \n");
    }
    else {
        printf("\n Correct Password.\n");
        pass = 1;
    }

    if (pass) { // do somelhing priviledged stuff
        printf("\n Root privileges given to the user.\n");
    }
    return 0;
}
