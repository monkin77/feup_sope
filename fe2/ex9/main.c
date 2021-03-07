#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 3

void *rot(void *arg )
{ // start routine of new threads
    *((int *)arg) *= *((int *)arg);     // need to return an adress that isn't a local variable | basically makes
    printf("\n\t In thread PID: %d ; TID: %lu with argument: %d.", getpid(), (unsigned long)pthread_self(), *(int *)arg);  // arg is the argument passed on pthread_create
    sleep(10);      // alinea B to see the threads with "ps -eLF"
    pthread_exit(arg); // return i*i
}

int main(void)
{
    int i;                   // thread counter
    pthread_t ids[NTHREADS]; // storage of (system) Thread Identifiers

    setbuf(stdout, NULL); // only for debugging
    printf("\nMain thread PID: %d ; TID: %lu.\n", getpid(), (unsigned long)pthread_self());

    int threadReturnValues[] = {0, 1, 2};

    // new threads creation
    for (i = 0; i < NTHREADS; i++)
    {
        if (pthread_create(&ids[i], NULL, rot, (void *) &threadReturnValues[i]) != 0)    // send i as the argument to each thread
            exit(-1); // here, we decided to end process
        else
            printf("\nNew thread %d ; TID: %lu.", i, (unsigned long)ids[i]);
    }
    // wait for finishing of created threads
    for (i = 0; i < NTHREADS; i++)
    {
        void* threadReturnValue;
        pthread_join(ids[i], &threadReturnValue); // Note: threads give no termination code
        
        int convertedReturnValue = *((int *)(threadReturnValue));
        printf("\nTermination of thread %d: %lu with return value: %d.", i, (unsigned long)ids[i], convertedReturnValue);
    }

    printf("\n");
    pthread_exit(NULL); // here, not really necessary...
    return 0;           // will not run this!
}