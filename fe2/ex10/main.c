#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 2

static int writtenFirstMessage = 0;

struct funcArgument{
    char* toBeWritten;
    int order;
};

void *displaySequence(void *arg){ // start routine of new threads
    struct funcArgument* farg =  (struct funcArgument*) arg ;
    if(farg->order == 1){
        printf(farg->toBeWritten);
        writtenFirstMessage = 1;
    }
    else if(farg->order == 2){
        while(1){
            if(writtenFirstMessage == 1){
                printf(farg->toBeWritten);
                break;
            }
            sleep(1);
        }
    }
    
    pthread_exit(arg);
}


int main(void){
    int i;                   // thread counter
    pthread_t ids[NTHREADS]; // storage of (system) Thread Identifiers

    setbuf(stdout, NULL); // only for debugging
    //printf("\nMain thread PID: %d ; TID: %lu.\n", getpid(), (unsigned long)pthread_self());

    struct funcArgument *arguments;
    arguments = (struct funcArgument*)malloc(sizeof(struct funcArgument)*2);
   
    arguments[0].order = 1, arguments[0].toBeWritten = "Operating";
    arguments[1].order = 2, arguments[1].toBeWritten = " Systems";
    
    // new threads creation
    for (i = 0; i < NTHREADS; i++)
    {
        if (pthread_create(&ids[i], NULL, displaySequence, (void *) &arguments[i] ) != 0)    // send i as the argument to each thread
            exit(-1); // here, we decided to end process
        else
            ;
    }
    
    // wait for finishing of created threads
    for (i = 0; i < NTHREADS; i++)
    {

        pthread_join(ids[i], NULL); // Note: threads give no termination code
        
        //printf("\nTermination of thread %d: %lu with return value: %d.", i, (unsigned long)ids[i], convertedReturnValue);
    }

    printf("\n");
    pthread_exit(NULL); // here, not really necessary...
    return 0;           // will not run this!
}