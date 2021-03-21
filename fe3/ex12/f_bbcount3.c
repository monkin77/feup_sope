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

pthread_cond_t* conds;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {
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
    conds = (pthread_cond_t*) malloc(nthreads*sizeof(pthread_cond_t));
	for (i = 0; i < nthreads; i++) {
        int* i2 = (int*) malloc(sizeof(int));
        *i2 = i;
        pthread_cond_init(&conds[i], NULL);
        if (i%2 == 0) {
            if (pthread_create(&ptid[i], NULL, thr_fun_inc, i2) != 0) {
                perror("pthread_create");
                exit(3);
            }
        } else {
            if (pthread_create(&ptid[i], NULL, thr_fun_dec, i2) != 0) {
                perror("pthread_create");
                exit(3);
            }
        }
	}
	for (i = 0; i < nthreads; i++)
		pthread_join(ptid[i], NULL);

	printf("\nEND!\n");
	return 0;
}

void *thr_fun_inc(void *arg) {
    int i = *((int*) arg);
    pthread_mutex_lock(&lock);
	while (iter < MAX_ITER) {
        if (i == active_process) {
            printf("\n%ld %ld", count, iter);
            iter++;
            count++;
            active_process = (active_process + 1) % nthreads;
            pthread_cond_signal(&conds[active_process]);
        } else {
            pthread_cond_wait(&conds[i], &lock);        // releases a lock specified (2nd argument) and wait on cond. variable
        }
	}
    pthread_mutex_unlock(&lock); 
	printf("\nEND thread %lu!\n", (unsigned long)pthread_self());
	return (NULL);
}

void *thr_fun_dec(void *arg) {
    int i = *((int*) arg);
    pthread_mutex_lock(&lock);
	while (iter < MAX_ITER) {
        printf("\niter");
        if (i == active_process) {
            printf("\n%ld %ld", count, iter);
            iter++;
            count--;
            active_process = (active_process + 1) % nthreads;
            pthread_cond_signal(&conds[active_process]);
        } else {
            pthread_cond_wait(&conds[i], &lock);    // releases a lock specified (2nd argument) and wait on cond. variable
        }
	}
    pthread_mutex_unlock(&lock); 
	printf("\nEND thread %lu!\n", (unsigned long)pthread_self());
	return (NULL);
}
