/* Testing access issues to shared variables
 * - Race conditions!
 * JMMC - Out.2001
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUF_SIZE 20
#define MAX_ITER 100000
long count = BUF_SIZE;
void *thr_fun_inc(void *);
void *thr_fun_dec(void *);
int active_process = 0;
long iter = 0;
int nthreads;

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
	for (i = 0; i < nthreads; i++) {
        if (i%2 == 0) {
            if (pthread_create(&ptid[i], NULL, thr_fun_inc, i) != 0) {
                perror("pthread_create");
                exit(3);
            }
        } else {
            if (pthread_create(&ptid[i], NULL, thr_fun_dec, i) != 0) {
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
	while (iter < MAX_ITER) {
        if (active_process == arg) {
            printf("\n%ld", count);
            iter++;
            count++;
            active_process = (active_process + 1) % nthreads;
        }
	}
	printf("\nEND thread %lu!\n", (unsigned long)pthread_self());
	return (NULL);
}

void *thr_fun_dec(void *arg) {
	while (iter < MAX_ITER) {
        if (active_process == arg) {
            printf("\n%ld", count);
            iter++;
            count--;
            active_process = (active_process + 1) % nthreads;
        }
	}
	printf("\nEND thread %lu!\n", (unsigned long)pthread_self());
	return (NULL);
}
