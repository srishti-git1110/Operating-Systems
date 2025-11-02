#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("parent process, PID: %d\n", getpid());
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child process, PID: %d\n", getpid());
    } else {
        int wc = wait(NULL);
        printf("executing parent process after waiting for child to finish, PID: %d (waited for child PID: %d)\n", getpid(), wc);
    }
    return 0;
}