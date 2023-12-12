#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: forkloop <iterations>\n");
        exit(1);
    }

    int iterations = strtol(argv[1], NULL, 10);
    int rootpid = getpid();
    int stat = 0;

    for (int i = 0; i < iterations; i++) {
        if (getpid() == rootpid) {
            int n = fork();
            if (n < 0) {
            perror("fork");
            exit(1);
            } 
            if (n > 0) {
            wait(&stat);
            }
        }

        printf("ppid = %d, pid = %d, i = %d\n", getppid(), getpid(), i);
    }

    return 0;
}
