// memory virtualization (need to disable address space randomization to be able to see it in action)
// gcc -Wall -o virtualization/2/mem virtualization/2/mem.c
// ./mem & ; ./mem &; ./mem &; ./mem &

/*
each running program allocates the same address and the updation of *p still happens independently
almost as if there were two physical (main) memories
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char* argv[]) {
    int* p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) address stored in p: %p\n", getpid(), p);
    *p = 0;
    while (1) {
        sleep(5);
        *p = *p + 1;
        printf("(%d) value at address stored in p: %d\n", getpid(), *p);
    }
    return 0;
}