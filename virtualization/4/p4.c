#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    printf("parent process, PID: %d\n", getpid());
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child process, PID: %d\n", getpid()); // prints to the std output stream
        close(STDOUT_FILENO); // close the standard output file descriptor
        int fd = open("virtualization/4/outputfile.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU); // create a new file and set it as the standard output

        if (fd < 0) {
            fprintf(stderr, "failed to open file\n");
            exit(1);
        }

        char* newArgs[4];
        newArgs[0] = strdup("ls");
        newArgs[1] = strdup("-l");
        newArgs[2] = strdup("virtualization/4");
        newArgs[3] = NULL;
        execvp(newArgs[0], newArgs);
        fprintf(stderr, "execvp failed\n");
        exit(1);
    } else {
        int wc = wait(NULL);
        printf("parent process after waiting for child to finish, PID: %d (waited for child PID: %d)\n", getpid(), wc); // prints to the std output stream
    }
    return 0;
}