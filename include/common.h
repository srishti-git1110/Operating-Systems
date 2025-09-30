#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int Pthread_create(
    pthread_t* thread, 
    const pthread_attr_t* attr,
    void* (*start_routine)(void*),
    void* arg
) {
    int rc = pthread_create(thread, attr, start_routine, arg);
    if (rc != 0) {
        fprintf(stderr, "pthread_create error\n");
        exit(1);
    }
    return rc;
}

int Pthread_join(pthread_t thread, void** value_ptr) {
    int rc = pthread_join(thread, value_ptr);
    if (rc != 0) {
        fprintf(stderr, "pthread_join error\n");
        exit(1);
    }
    return rc;
}