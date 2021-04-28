#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

int main() {
	printf("Please insert characters\n");

    char s[1000];

    scanf("%s", s);
    
    for(int i = 0; s[i] != '\0'; i++){
        s[i] = toupper(s[i]);
    }   
    
    printf("%s\n", s);

    return 0;
}