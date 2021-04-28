#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ITER 10

int main(int argc, char* argv[]) {
    FILE *fd_in = NULL;
    FILE *fd_out = NULL;

    if(argc > 1){
        char* in = argv[1];
        fd_in = fopen(in, "r");
        if(fd_in == NULL){
            printf("There is no such file with that name!\n"),
            exit(2);
        }

        if(argc > 2){
            char* out = argv[2];
            fd_out = fopen(out, "w");
        }
    }

    if(fd_in == NULL) fd_in = stdin;
    if(fd_out == NULL) fd_out = stdout;

    char s[1000];

    int iter = 0;
    while( fgets(s, sizeof(s), fd_in) && iter < MAX_ITER){
        for(int i = 0; s[i] != '\0'; i++){
            if(s[i] == '\n') s[i] = '\0';
            s[i] = toupper(s[i]);
        }   
    
        fprintf(fd_out, "%s\n", s);
        iter++;
    }
    
    

    if(fd_in != stdin) fclose(fd_in);
    if(fd_out != stdout) fclose(fd_out);

    return 0;
}