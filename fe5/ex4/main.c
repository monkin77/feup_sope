#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

int main() {
    long clockTicks = sysconf(_SC_CLK_TCK);

    printf("No. clock ticks: %lu\n", clockTicks);

    struct timeval timeOfDay;
    struct timezone tz;
    
    timeOfDay.tv_sec = 1619605206;
    timeOfDay.tv_usec = 0;

    int result = settimeofday(&timeOfDay, NULL);

    gettimeofday(&timeOfDay, NULL);
    // since the operation is not permitted, it doesn't throw an error in the console. So we have to catch it with strerror(errno) which is set automatticaly.
    printf("curr time of day: %sreturn value: %d errno: %s\n", ctime(&timeOfDay.tv_sec), result, strerror(errno));

    char* time = ctime(&timeOfDay.tv_sec);

    printf("time: %s\n", time);

    printf("size of system variable that hold real time: %lu\n", sizeof(timeOfDay.tv_sec) );

    return 0;
}