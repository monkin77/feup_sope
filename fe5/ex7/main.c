#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    char c;
	struct termios tms, tms_ini;

	tcgetattr(STDIN_FILENO, &tms_ini); // read console's configuration
	tms = tms_ini;
    
    printf("\nInsert your username\n");

	char username[100];
	char password[100];
	int userIdx = 0;
	int passIdx = 0;

	do {
		if (read(STDIN_FILENO, &c, 1) != 1)
			perror("read failed");
		else{
			username[userIdx] = c;
			userIdx++;
			printf("***");
		}
		} while (c != '\n');	// wait for [ENTER]

	printf("\nUsername: %s", username);

    /* 

	tms.c_lflag &= ~ECHO; // inhibit char echoing
	tcsetattr(STDIN_FILENO, TCSANOW, &tms); // set new configuration
	*/

	tcsetattr(STDIN_FILENO, TCSANOW, &tms_ini);	// reset configuration
	// experiment this program with the above line commented! ;-)
	printf("\nInitial console configuration has been reset!\n");

	
    return 0;
}