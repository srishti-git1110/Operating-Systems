#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("hellow world, PID: %d\n", getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello from child, PID: %d\n", getpid());
    } else {
        printf("hello from parent, PID: %d, child PID: %d\n", getpid(), rc);
    }
}