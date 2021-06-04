#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main() {
	printf("Please insert characters\n");

    char s[10000];

    while(scanf("%s", s) != EOF) {
        for(int i = 0; s[i] != '\n'; i++){
            s[i] = toupper(s[i]);
        }   
    
        printf("%s\n", s);

        memset(s, NULL, 1000);
    }

    return 0;
}