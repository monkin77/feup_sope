#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void *garbage_collected_malloc(size_t size) {
    void *p = malloc(size);
    free(p);
    return p;
}

int main(int argc, char **argv) {
    char *buf;
    int i;

    if (argc < 2) {
        fprintf(stderr, "\nUsage: %s <string>\n", argv[0]);
        exit(1);
    }
    
    size_t stringSize = 1;
    char* currChar = argv[1];
    while(*currChar != '\0'){
        stringSize++;
        currChar++;
    }

    printf("Input string: %s with size %ld\n", argv[1], stringSize);

    buf = (char *)garbage_collected_malloc(stringSize);
    strncpy(buf, argv[1], stringSize);
    for (i = 0; i < stringSize; i++) {
        buf[i] = toupper(buf[i]);
    }
    printf("Output string: %s\n", buf);
    return 0;
}