#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void testStackSmashing(){
    char buff[15];  // is on uninitialized memory area
    int pass = 0;   // is on initialized memory area

    printf("\n Enter the password : \n");

    gets(buff);
    // fgets(buff, 13, stdin); // changed to this
    
    // printf("Address of buff: %p and addr of pass: %p\n", buff, &pass);

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
}

int main(void){
    testStackSmashing();

    return 0;
}

