/*
*	EXEC: 1st example of typical usage!
*
* Note:	execve is the syscal!
*	execv, execvp, execvpe, execl, execlp, execle are library functions.
*
* Exercise:
* 	change this code to show that USER was changed after the exec.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


// preparation for execve:
char *cmdline[] = { "printenv", "USER", (void *)0};
char *newenviron[] = { "USER=Linus", NULL };

int main() {
	pid_t id;
setbuf(stdout, NULL);	// to make sure printf() have no buffer so, nodelay!

printf("\nParent: %d. USER=%s", getpid(), getenv("USER"));

id = fork();
switch (id) {
	case -1:
		perror ("fork()");
		exit (1);
	case 0:	// child
		printf("\nChild: %d. USER=%s", getpid(), getenv("USER"));
		printf("\nChild: check that following exec was succeful with: \"ps x | grep sleep\"\n");
		if (execvpe("/bin/printenv", cmdline, newenviron) == -1)
			perror("execve");
		printf("\nYou will not see this unless execve() fails! Know why?...\n");
		break;	// if execve fails...
	default:
		printf("\nParent before: %d. USER=%s", getpid(), getenv("USER"));
		pid_t pid = wait(0);
		printf("Child %d ended\n", pid);
	}
	return 0;
}
