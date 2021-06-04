/* Testing access issues to shared variables
 * - Race conditions!
 * JMMC - Out.2001
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAXCOUNT 100000
long count;
void *thr_fun(void *);

pthread_mutex_t lock;

int main(int argc, char *argv[]) {
    pthread_t *ptid;
    int nthreads;
    int i;

    setbuf(stdout, NULL);
    if (argc < 2)
    {
        printf("\nUsage: %s #threads\n", argv[0]);
        exit(1);
    }
    nthreads = atoi(argv[1]);
    ptid = (pthread_t *)malloc(nthreads * sizeof(pthread_t));

    if (ptid == NULL)
    {
        perror("malloc");
        exit(2);
    }

    if (pthread_mutex_init(&lock, NULL) != 0)   // Creates a mutex
    {
        printf("\nmutex init has failed\n");
        return 1;
    }

    for (i = 0; i < nthreads; i++)
    {
        if (pthread_create(&ptid[i], NULL, thr_fun, NULL) != 0)
        {
            perror("pthread_create");
            exit(3);
        }
    }
    for (i = 0; i < nthreads; i++)
        pthread_join(ptid[i], NULL);

    pthread_mutex_destroy(&lock);   // Deletes a mutex object

    printf("\nEND!\n");
    return 0;
}

void *thr_fun(void *arg) {
    printf("\nCreated thread %lu\n", (unsigned long)pthread_self());

    while (1){
        pthread_mutex_lock(&lock);  // If mutex is already locked, the thread waits for the mutex to be available
        if(count >= MAXCOUNT){
            pthread_mutex_unlock(&lock); // Releases a mutex object, if one or more threads are waiting, it causes one of those to start
            break;
        }
        count++;
        printf("%ld\n", count);
        pthread_mutex_unlock(&lock); // Releases a mutex object, if one or more threads are waiting, it causes one of those to start
    }

    printf("\nEND thread %lu!\n", (unsigned long)pthread_self());

    return (NULL);
}

/*
	To see the access problems, run: ./count 15 | uniq -cd
*/