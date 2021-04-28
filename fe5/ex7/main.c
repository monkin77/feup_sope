#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    char c;
	struct termios tms, tms_ini;

	tcgetattr(STDIN_FILENO, &tms_ini); // read console's configuration
	tms = tms_ini;
    
    printf("\nInsert your username\n");

	char username[10000];
	char password[10000];
	int userIdx = 0;
	int passIdx = 0;

	do {
		if (read(STDIN_FILENO, &c, 1) != 1)
			perror("read failed");
		else{
			username[userIdx] = c;
			userIdx++;
		}
		} while (c != '\n');	// wait for [ENTER]

	tms.c_lflag &= ~ICANON; // Disable Canonical mode (Start reading 1 char at a time)
	tms.c_lflag &= ~ECHO; // inhibit char echoing (Since we want to show '*' instead)

	tcsetattr(STDIN_FILENO, TCSANOW, &tms); // set new configuration

	printf("Insert your password\n");

	do {
		if (read(STDIN_FILENO, &c, 1) != 1)
			perror("read failed");
		else{
			if(c == 0x08){
				printf("backspace\n");
				passIdx--;
				password[passIdx] = ' ';
			}
			else{
				password[passIdx] = c;
				passIdx++;
			}
			write(STDIN_FILENO, &c, 1);
			write(STDIN_FILENO, "***", 3);
		}
		} while (c != '\n');	// wait for [ENTER]

	printf("\nUsername: %s", username);
	printf("\nPassword: %s", password);


	tcsetattr(STDIN_FILENO, TCSANOW, &tms_ini);	// reset configuration
	// experiment this program with the above line commented! ;-)

	printf("\nInitial console configuration has been reset!\n");

	
    return 0;
}