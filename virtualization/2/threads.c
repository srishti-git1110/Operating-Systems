// for a large value of `loops`, the final value of `counter` is often unexpected.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "include/common.h"

volatile int counter = 0;
int loops;

void* worker(void* arg) {
    for (int i = 0; i < loops; i++) {
        counter++;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: threads <loops>\n");
        exit(1);
    }

    loops = atoi(argv[1]);
    pthread_t t1, t2;
    printf("initial value of counter: %d\n", counter);

    Pthread_create(&t1, NULL, worker, NULL);
    Pthread_create(&t2, NULL, worker, NULL);

    Pthread_join(t1, NULL);
    Pthread_join(t2, NULL);

    printf("final value of counter: %d\n", counter);
    return 0;
}
