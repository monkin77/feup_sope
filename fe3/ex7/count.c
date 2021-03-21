/* Testing access issues to shared variables
 * - Race conditions!
 * JMMC - Out.2001
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAXCOUNT 100
long count;
void *thr_fun(void *);
int turn = 0;

struct argToThread {
	int index;
	int nthreads;
};

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

	struct argToThread args[nthreads];

	for (i = 0; i < nthreads; i++){
		args[i].index = i;
		args[i].nthreads = nthreads;
		if (pthread_create(&ptid[i], NULL, thr_fun, (void *) &args[i]) != 0)
		{
			perror("pthread_create");
			exit(3);
		}
	}
	for (i = 0; i < nthreads; i++)
		pthread_join(ptid[i], NULL);

	printf("\nEND!\n");
	return 0;
}

void *thr_fun(void *arg) {
	struct argToThread *argValues = (struct argToThread *) arg;
	int index = argValues->index;
	int numThreads = argValues->nthreads;
	// printf("\nCreated thread %lu\n", (unsigned long)pthread_self());

	printf("Thread with index: %d and numThreads is: %d\n", index, numThreads);
    while (count < MAXCOUNT) {
		if(turn == index){
			printf("%ld\n", count);
			count++;
			turn = (turn+1)%numThreads;
		}
	}
	printf("\nEND thread %lu!\n", (unsigned long)pthread_self());

	return (NULL);
}

/*
	To see the access problems, run: ./count 15 | uniq -cd
*/