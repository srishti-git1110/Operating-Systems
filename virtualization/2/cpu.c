// A very basic program to understand virtualization of the processor by the OS
// gcc -Wall -o virtualization/2/cpu virtualization/2/cpu.c
/* ./cpu A &; ./cpu B &; ./cpu C &; ./cpu D & 
and see the output to understand what happened. 
Even though there's a single CPU available, these programs all run at the same time as can be understood from the output. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

int 
main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: cpu <string>\n");
        exit(1);
    }
    struct timeval start;
    gettimeofday(&start, NULL);
    
    char* str = argv[1];
    int counter = 0;
    while (counter <= 5) {
        // sleep(10);
        printf("Start time: %ld.%06d\n", start.tv_sec, start.tv_usec);
        printf("(%d) %s\n", getpid(), str);
        counter++;
    }
}
