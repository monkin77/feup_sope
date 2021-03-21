/* Testing access issues to shared variables
 * - Race conditions!
 * JMMC - Out.2001
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h> 

#define BUF_SIZE 20
#define MAX_ITER 100000
void *thr_fun_inc(void *);
void *thr_fun_dec(void *);
int active_process = 0;
int nthreads;
long iter = 0;
long count = BUF_SIZE;

sem_t mutex;

int main(int argc, char *argv[]) {
    sem_init(&mutex, 0, 1);
	pthread_t *ptid;
	int i;

	setbuf(stdout, NULL);
	if (argc < 2) {
		printf("\nUsage: %s #threads\n", argv[0]);
		exit(1);
	}
	nthreads = atoi(argv[1]);
	ptid = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
	if (ptid == NULL) {
		perror("malloc");
		exit(2);
	}
	for (i = 0; i < nthreads; i++) {
        if (i%2 == 0) {
            if (pthread_create(&ptid[i], NULL, thr_fun_inc, (void*) NULL) != 0) {
                perror("pthread_create");
                exit(3);
            }
        } else {
            if (pthread_create(&ptid[i], NULL, thr_fun_dec, (void*) NULL) != 0) {
                perror("pthread_create");
                exit(3);
            }
        }
	}
	for (i = 0; i < nthreads; i++)
		pthread_join(ptid[i], NULL);

	printf("\nEND!\n");
    sem_destroy(&mutex);
	return 0;
}

void *thr_fun_inc(void *arg) {
	while (iter < MAX_ITER) {
        sem_wait(&mutex);
        printf("\n%ld", count);
        iter++;
        count++;
        sem_post(&mutex);
	}
	printf("\nEND thread %lu!\n", (unsigned long)pthread_self());
	return (NULL);
}

void *thr_fun_dec(void *arg) {
	while (iter < MAX_ITER) {
        sem_wait(&mutex);
        printf("\n%ld", count);
        iter++;
        count--;
        sem_post(&mutex);
	}
	printf("\nEND thread %lu!\n", (unsigned long)pthread_self());
	return (NULL);
}
