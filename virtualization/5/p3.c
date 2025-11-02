#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("hello world from parent process, PID: %d\n", getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child process, PID: %d\n", getpid());
        char* newArgs[3];
        newArgs[0] = strdup("wc");
        newArgs[1] = strdup("virtualization/4/p3.c");
        newArgs[2] = NULL;
        execvp(newArgs[0], newArgs);
        // execvp only returns if there is an error
        fprintf(stderr, "execvp failed\n");
        exit(1);
    } else {
        int wc = wait(NULL);
        printf("parent process after waiting for child to finish, PID: %d (waited for child PID: %d)\n", getpid(), wc);
    }
    return 0;
}