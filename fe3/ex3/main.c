#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void func(int signo) {
  fprintf(stdout, "Proccess %d Received signal %d!\n", getpid(), signo);
}

int main(int argc, char *argv[], char *envp[]) {
  int pid = fork();

  struct sigaction new, old;
  sigset_t smask; // defines signals to block while func() is running

  //  prepare struct sigaction
  if (sigemptyset(&smask) == -1) //  block no signal
    perror("sigsetfunctions");
  new.sa_handler = func; //  function that will be called with the new signal
  new.sa_mask = smask;
  new.sa_flags = 0; //  usually works

  if (sigaction(SIGUSR1, &new, &old) == -1)
    perror("sigaction\n");
  if (sigaction(SIGINT, &new, &old) == -1)
    perror("sigaction\n");

  switch (pid) {
  case -1:
    perror("fork");
    exit(1);
  case 0:; //  case child
    fprintf(stdout, "The parent pid is %d and the child pid is %d\n", getppid(),
            getpid());
    int cpid = fork(); // child pid

    switch (cpid) {
    case -1:
      perror("fork");
      exit(1);
    case 0: //  grandchild
      fprintf(stdout, "The child pid is %d and the grandchild pid is %d\n",
              getppid(), getpid());
      sleep(20);
      exit(0);
      break;
    default: //  child
      sleep(20);
      // kill(cpid, SIGUSR1);
      exit(0);
      break;
    }
    break;
  default: //  case parent
    sleep(1);
    //kill(pid, SIGUSR1);
    sleep(20);
    exit(0);
    break;
  }

  return 0;
}